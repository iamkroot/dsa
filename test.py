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


def compile(filepath: Path):
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


def test_file(filepath: Path, testfile=None):
    build_obj = compile(filepath)
    if not build_obj:
        return
    if testfile:
        tests_dir = get_tests_dir(testfile)
    else:
        tests_dir = get_tests_dir(filepath)
    if not tests_dir:
        return
    test_files = list(tests_dir.iterdir())
    input_files = filter(lambda x: x.suffix == ".in", test_files)
    output_files = filter(lambda x: x.suffix == ".out", test_files)
    for input_file, output_file in zip(input_files, output_files):
        with open(input_file) as inp:
            call = sp.run(str(build_obj), stdin=inp, capture_output=True)
            actual_output = call.stdout.decode().strip('\r\n')
        with open(output_file) as expected:
            expected_output = expected.read().strip('\r\n')
        if expected_output != actual_output:
            print("Failed for test case ", input_file)
            print_diff(expected_output, actual_output)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("paths", nargs="*")
    args = parser.parse_args()
    if not args.paths:
        args.paths = list(Path('.').glob("**/*.c"))

    for path in args.paths:
        path = Path(path)
        testfile = None
        if not path.exists():
            return
        if path.is_dir():
            args.paths += path.glob("**/*.c")
            continue
        if path.stem == 'main':
            with open(path) as f:
                line = f.readline()
            if not line.startswith('//'):
                continue
            testfile = Path(line[3:].strip())
        test_file(path, testfile)


if __name__ == "__main__":
    main()
