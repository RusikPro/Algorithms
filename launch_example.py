import os
import sys
import subprocess

def build_and_run(source_relative_path):
    # Define the build and source base directories
    project_dir = os.path.dirname(os.path.realpath(__file__))
    build_dir = os.path.join(project_dir, 'build')

    # Change to the build directory, create if necessary
    if not os.path.exists(build_dir):
        os.makedirs(build_dir)
    os.chdir(build_dir)

    # Run CMake to configure the project
    cmake_command = ['cmake', '..']
    print("Configuring project with CMake...")
    if subprocess.call(cmake_command) != 0:
        print("CMake configuration failed")
        return

    # Build the project with make
    print("Building project...")
    if subprocess.call(['make']) != 0:
        print("Build failed")
        return

    # Extract chapter name and file name from the source_relative_path
    path_parts = source_relative_path.split('/')
    if len(path_parts) < 3:
        print("Invalid path provided. Please use the format <chapter_folder>/cpp/exercises/<filename>")
        return

    chapter_name = path_parts[0].replace('_', ' ').title().replace(' ', '_')
    file_name = path_parts[-1]
    executable_name = os.path.splitext(file_name)[0]  # Remove extension from file name
    executable_full_name = f"{chapter_name.lower()}_{executable_name}"

    # Construct the path to the executable
    executable_full_path = os.path.join(build_dir, chapter_name, executable_full_name)


    # Construct the path to the executable
    executable_full_path = os.path.join(build_dir, chapter_name, executable_name)

    # chapter_name = path_parts[0].replace('_', ' ').title().replace(' ', '_')
    # file_name = path_parts[-1]  # Get the actual file name
    # subfolder_name = path_parts[-2]  # Extract the subfolder (e.g., 'search')

    # # Generate the executable name dynamically based on file structure
    # executable_name = f"{subfolder_name}_{os.path.splitext(file_name)[0]}"  # Combine subfolder and file name

    # # Generate the full executable name
    # executable_full_name = f"{chapter_name.lower()}_{executable_name}"

    # # Construct the path to the executable
    # executable_full_path = os.path.join(build_dir, chapter_name, executable_full_name)

    # Check if the executable exists
    if not os.path.exists(executable_full_path):
        print(f"Executable not found: {executable_full_path}")
        return

    # Run the executable
    print(f"Running {executable_full_path}...")
    subprocess.call([executable_full_path])

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python launch_example.py <relative/path/to/source_executable>")
        sys.exit(1)

    source_exec_path = sys.argv[1]
    build_and_run(source_exec_path)
