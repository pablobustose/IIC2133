import argparse
import sys
from itertools import product
from pathlib import Path

Tiles = list[list[str]]
Map = list[list[int]]
SettedTiles = dict[tuple[int, int], list[str]]


should_fail = False


def parse_input(input_path: Path):
    """
    This function reads the input file and parses the data.
    It returns the height and width of the map, the tiles, and the setted tiles.
    """
    input_data = input_path.read_text().splitlines()
    width, height = map(int, input_data[0].split(" "))
    tiles = [input_data[di + 2].split(" ") for di in range(int(input_data[1]))]
    offset = 2 + int(input_data[1])

    setted_tiles = {
        (x, y): tiles[idx]
        for (x, y, idx) in (
            map(int, input_data[offset + di + 1].split(" "))
            for di in range(int(input_data[offset]))
        )
    }

    return height, width, tiles, setted_tiles


def parse_output(output_path: Path):
    """
    This function reads the output file and parses the data.
    It returns the map to check.
    """
    try:
        map_to_check = [
            [int(entry) for entry in line.strip().split(" ")]
            for line in output_path.read_text().splitlines()
        ]
        return map_to_check
    except Exception:
        print("Invalid output map (must be a matrix of integers)")
        sys.exit(1)


def validate_size(map_to_check: Map, height: int, width: int):
    """
    This function validates the size of the map.
    It checks if the map's dimensions match the expected height and width.
    """
    if len(map_to_check) != height or any(len(row) != width for row in map_to_check):
        print("Invalid output map (wrong size)")
        sys.exit(1)


def validate_starting_tiles(map_to_check: Map, tiles: Tiles, setted_tiles: SettedTiles):
    """
    This function validates the starting tiles of the map.
    It checks if the starting tiles match the expected tiles.
    """
    global should_fail

    for (x, y), tile in setted_tiles.items():
        idx = tiles.index(tile)
        if map_to_check[y][x] != idx:
            print("Invalid output map (wrong starting tiles)")
            should_fail = True


def validate_border(map_to_check: Map, tiles: Tiles, height: int, width: int):
    """
    This function validates the borders of the map.
    It checks if the borders match the expected tiles.
    """
    global should_fail

    for x, y in product(range(width), range(height)):
        idx = map_to_check[y][x]
        tile = tiles[idx]
        if x + 1 < width and tile[1] != tiles[map_to_check[y][x + 1]][3]:
            print(f"Invalid output map (wrong border at right of ({x}, {y}))")
            should_fail = True
        if y + 1 < height and tile[2] != tiles[map_to_check[y + 1][x]][0]:
            print(f"Invalid output map (wrong border at bottom of ({x}, {y}))")
            should_fail = True
        if x - 1 >= 0 and tile[3] != tiles[map_to_check[y][x - 1]][1]:
            print(f"Invalid output map (wrong border at left of ({x}, {y}))")
            should_fail = True
        if y - 1 >= 0 and tile[0] != tiles[map_to_check[y - 1][x]][2]:
            print(f"Invalid output map (wrong border at top of ({x}, {y}))")
            should_fail = True


def main(input_path: Path, output_path: Path):
    """
    This is the main function.
    It validates the input and output paths, parses the input and output files,
    validates the size, starting tiles, and borders of the map.
    If any validation fails, it exits the program with an error.
    """
    if not input_path.is_file() or not output_path.is_file():
        print("Invalid input/output path")
        sys.exit(1)

    map_to_check = parse_output(output_path)
    height, width, tiles, setted_tiles = parse_input(input_path)
    validate_size(map_to_check, height, width)
    validate_starting_tiles(map_to_check, tiles, setted_tiles)
    validate_border(map_to_check, tiles, height, width)
    if should_fail:
        sys.exit(1)


if __name__ == "__main__":
    """
    This script is used to validate the borders of a map.
    It checks if the borders match the expected tiles.
    If any validation fails, it exits the program with an error.

    Example usage:
    python check_backtracking.py --input /path/to/input/file.txt --output /path/to/output/file.txt
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=Path, help="Path to the input file.")
    parser.add_argument("output", type=Path, help="Path to the output file.")
    args = parser.parse_args()

    main(args.input, args.output)
