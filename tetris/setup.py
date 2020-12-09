import cx_Freeze

executables = [cx_Freeze.Executable("tetris.py", base="Win32GUI")]

cx_Freeze.setup(
    name="tetris",
    options={"build_exe": {"packages": ["pygame"]}},
    executables=executables
)
