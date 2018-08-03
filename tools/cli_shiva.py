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


def replace_occurences():
    replacements = {'project_name': args.project_name}
    replace_in_files(replacements, args.output_directory + "/CMakeLists.txt")
    os.rename(args.output_directory + "/project_name", args.output_directory + "/" + args.project_name)


print_option()
copy_template()
replace_occurences()
