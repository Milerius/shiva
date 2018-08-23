#!/usr/bin/env python3
import os
import sys
import argparse
from distutils.dir_util import copy_tree


def get_script_path():
    return os.path.dirname(os.path.realpath(sys.argv[0]))


parser = argparse.ArgumentParser(description='cli tooling for shiva.')
parser.add_argument('--project_name', help='set the project name', default="basic_shiva_project")
parser.add_argument('--project_renderer', help='set the project renderer', default="sfml")
parser.add_argument('--output_directory', help='set the output directory of the project',
                    default=os.getcwd() + "/basic_shiva_project")
args = parser.parse_args()


def print_option():
    print("option are ", args.project_name, args.project_renderer)
    print("script running from directory:", get_script_path())
    print('configuring a project named', args.project_name, " with renderer", args.project_renderer)
    print('output directory', args.output_directory)


def copy_template():
    current_template_directory = get_script_path() + "/game_templates/" + args.project_renderer
    print("current_template_directory: ", current_template_directory)
    copy_tree(current_template_directory, args.output_directory)


def replace_in_files(replacements, filename):
    lines = []
    with open(filename) as infile:
        for line in infile:
            for src, target in replacements.items():
                line = line.replace(src, target)
            lines.append(line)
    with open(filename, 'w') as outfile:
        for line in lines:
            outfile.write(line)
        outfile.write('\n')


def replace_occurences():
    replacements = {'<project_name>': args.project_name,
                    'project_name': args.project_name,
                    '<PROJECT_NAME>': args.project_name.upper()}

    os.rename(args.output_directory + "/project_name/world/project_name_world.cpp",
              args.output_directory + "/project_name/world/" + args.project_name + "_world.cpp")
    os.rename(args.output_directory + "/project_name/world/project_name_world.hpp",
              args.output_directory + "/project_name/world/" + args.project_name + "_world.hpp")
    os.rename(args.output_directory + "/project_name", args.output_directory + "/" + args.project_name)

    for root, dirs, files in os.walk(args.output_directory):
        for file in files:
            print(os.path.join(root, file))
            extension = os.path.splitext(file)[1]
            if extension == ".avi":
                continue
            replace_in_files(replacements, os.path.join(root, file))

print_option()
copy_template()
replace_occurences()
