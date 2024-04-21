import os
import sys

def create_chapter_folder(chapter_name):
    # Define the base path for the chapter
    base_path = chapter_name

    # Subdirectories
    subdirs = ['cpp', 'py', 'exercises']

    # Create base chapter directory and subdirectories
    os.makedirs(base_path, exist_ok=True)
    for subdir in subdirs:
        os.makedirs(os.path.join(base_path, subdir), exist_ok=True)

    # Normalize chapter name for CMake usage (replace non-alphanumeric characters with "_")
    normalized_chapter_name = ''.join(c if c.isalnum() else '_' for c in chapter_name)

    # Create CMakeLists.txt for the chapter with necessary configurations
    cmake_path = os.path.join(base_path, 'CMakeLists.txt')
    with open(cmake_path, 'w') as cmake_file:
        cmake_file.write(f"""cmake_minimum_required(VERSION 3.10)
project({normalized_chapter_name})

# Main executable
add_executable({normalized_chapter_name}_main cpp/main.cpp)
target_link_libraries({normalized_chapter_name}_main PRIVATE common)
target_include_directories({normalized_chapter_name}_main PRIVATE ../common)

# Exercise executable
add_executable({normalized_chapter_name}_exercise exercises/exercise.cpp)
target_link_libraries({normalized_chapter_name}_exercise PRIVATE common)
target_include_directories({normalized_chapter_name}_exercise PRIVATE ../common)
""")

    # Create a placeholder C++ main file
    main_cpp_path = os.path.join(base_path, 'cpp', 'main.cpp')
    with open(main_cpp_path, 'w') as main_cpp:
        main_cpp.write("""#include <iostream>

int main () {{
    std::cout << "Hello from main in {}" << std::endl;
    return 0;
}}
""".format(chapter_name))

    # Create a placeholder Python script
    main_py_path = os.path.join(base_path, 'py', 'main.py')
    with open(main_py_path, 'w') as main_py:
        main_py.write(f"""# This is a placeholder Python script for {chapter_name}

def main ():
    print( "Hello from Python in {chapter_name}" )

if __name__ == "__main__":
    main()
""")

    # Create a placeholder C++ exercise file
    exercise_cpp_path = os.path.join(base_path, 'exercises', 'exercise.cpp')
    with open(exercise_cpp_path, 'w') as exercise_cpp:
        exercise_cpp.write("""#include <iostream>

int main () {{
    std::cout << "Exercise for {}" << std::endl;
    return 0;
}}
""".format(chapter_name))

    print(f"Created chapter folder structure for: {chapter_name}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python new_chapter.py <chapter_name>")
        sys.exit(1)

    chapter_name = sys.argv[1]
    create_chapter_folder(chapter_name)
