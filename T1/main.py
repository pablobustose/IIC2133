import difflib

def compare_files(file1_path, file2_path, output_path):
    with open(file1_path, 'r') as file1, open(file2_path, 'r') as file2:
        lines1 = file1.readlines()
        lines2 = file2.readlines()
    differ = difflib.Differ()
    diff = list(differ.compare(lines1, lines2))

    with open(output_path, 'w') as output_file:
        for line_number, line in enumerate(diff, start=1):
            if line.startswith('- '):
                output_file.write(f"Error en línea {line_number} del archivo 1:\n")
                output_file.write(line[2:] + '\n')
            elif line.startswith('+ '):
                output_file.write(f"Error en línea {line_number} del archivo 2:\n")
                output_file.write(line[2:] + '\n')

file1_path = 'output.txt'
file2_path = 'BST/solutions/medium/output-B-02.txt'
output_path = 'diferencias.txt'

compare_files(file1_path, file2_path, output_path)