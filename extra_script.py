import subprocess
Import("env")

try:
    ret = subprocess.run(["git", "rev-parse", "--short", "HEAD"], stdout=subprocess.PIPE, text=True, check=True)
    git_rev = ret.stdout.strip()
    print(f"Current Git revision: {git_rev}")
    env.Append(CPPDEFINES=[("GIT_HASH", f'\\"{git_rev}\\"')])
except Exception as e:
    print(f"Error getting git revision: {e}")
    env.Append(CPPDEFINES=[("GIT_HASH", f'\\"unknown\\"')])
