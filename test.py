#!/usr/bin/python3
import argparse
from pathlib import Path
import re
import subprocess as sp
import difflib


def get_tests_dir(filepath):
    try:
        num = re.findall(r"^\d+", filepath.name)[0]
    except IndexError:
        return None
    tests_dir = filepath.parent / "Tests" / num
    if not tests_dir.exists():
        print("Tests dir not found at", tests_dir)
        return None
    return tests_dir


def compile_file(filepath: Path):
    if not filepath.suffix == '.c':
        return
    filepath = filepath.resolve()
    build_out = filepath.with_suffix('.o')
    cmd = f'gcc "{filepath!s}" -o "{build_out!s}"'
    sp.run(cmd, stdout=sp.PIPE, shell=True)
    if not build_out.exists():
        return
    return build_out


def print_diff(texta: str, textb: str):
    a = texta.splitlines(keepends=True)
    b = textb.splitlines(keepends=True)
    diff = difflib.unified_diff(a, b, n=1)
    print(*list(diff))


def run_tests(filepath: Path, testfile=None):
    tests_dir = get_tests_dir(testfile or filepath)
    if not tests_dir:
        return
    build_obj = compile_file(filepath)
    if not build_obj:
        return
    print("Running tests for", filepath)
    success = True
    test_files = list(tests_dir.iterdir())
    input_files = filter(lambda file: file.suffix == ".in", test_files)
    output_files = filter(lambda file: file.suffix == ".out", test_files)
    for input_file, output_file in zip(input_files, output_files):
        with open(input_file) as inp:
            call = sp.run(str(build_obj), stdin=inp, capture_output=True)
            actual_output = call.stdout.decode().strip('\r\n')
        with open(output_file) as expected:
            expected_output = expected.read().strip('\r\n')
        if expected_output != actual_output:
            print("Failed for test case", input_file)
            print_diff(expected_output, actual_output)
            success = False
    build_obj.unlink()
    return success


def gather_files(paths):
    if not paths:
        paths = list(Path('.').rglob("*.c"))

    for path in paths:
        path = Path(path)
        testfile = None
        if not path.exists():
            print(f"Path {path} not found.")
            continue
        if path.is_dir():
            paths += path.rglob("*.c")
            continue
        if path.stem == 'main':
            with open(path) as f:
                line = f.readline()
            if not line.startswith('//'):
                continue
            testfile = Path(line[3:].strip())
        yield path, testfile


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("paths", nargs="*")
    args = parser.parse_args()
    files = list(gather_files(args.paths))
    for path, testfile in files:
        if run_tests(path, testfile):
            print("All tests passed.")


if __name__ == "__main__":
    main()
