const assert = require('assert');
const fs = require('fs');
const path = require('path');


const SOLUTIONS_PART1 = {
  'sample1.txt': 21,
  'input.txt': 1698,
};
const SOLUTIONS_PART2 = {
  'sample1.txt': 8,
  'input.txt': 672280,
};


function solve(filePath) {
  const fileName = path.basename(filePath)
  console.log(`### ${fileName} ###`)

  if (fileName in SOLUTIONS_PART1) {
    const solutionPart1_ = solvePart1(filePath);
    console.log(`Part 1: ${solutionPart1_}`);
    const solutionPart1 = SOLUTIONS_PART1[fileName];
    assert(solutionPart1_ === solutionPart1);
  }

  if (fileName in SOLUTIONS_PART2) {
    const solutionPart2_ = solvePart2(filePath);
    console.log(`Part 2: ${solutionPart2_}`);
    const solutionPart2 = SOLUTIONS_PART2[fileName];
    // assert(solutionPart2_ === solutionPart2);
  }
}


function solvePart1(filePath) {
  const { grid, size } = loadGrid(filePath);

  const initMask = () => Array(size).fill().map(() => Array(size).fill(-1));

  const north = initMask();
  const south = initMask();
  for (let x = 0; x < size; ++x) {
    for (let y = 1; y < size; ++y)
      north[y][x] = Math.max(north[y - 1][x], grid[y - 1][x]);
    for (let y = size - 2; y >= 0; --y)
      south[y][x] = Math.max(south[y + 1][x], grid[y + 1][x]);
  }

  const west = initMask();
  const east = initMask();
  for (let y = 0; y < size; ++y) {
    for (let x = 1; x < size; ++x)
      west[y][x] = Math.max(west[y][x - 1], grid[y][x - 1]);
    for (let x = size - 2; x >= 0; --x)
      east[y][x] = Math.max(east[y][x + 1], grid[y][x + 1]);
  }

  let solution = 0;
  for (let y = 0; y < size; ++y)
    for (let x = 0; x < size; ++x)
      solution += grid[y][x] > Math.min(north[y][x], south[y][x], west[y][x], east[y][x]);
  return solution;
}


function solvePart2(filePath) {
  const { grid, size } = loadGrid(filePath);

  const initMask = () => {
    return Array(size).fill().map(() => Array(size).fill().map(() => Array(10).fill(0)));
  };

  const north = initMask();
  const south = initMask();
  for (let x = 0; x < size; ++x) {
    for (let y = 1; y < size; ++y) {
      for (let i = 0; i <= grid[y - 1][x]; ++i) north[y][x][i] = 1;
      for (let i = grid[y - 1][x] + 1; i < 10; ++i) north[y][x][i] = north[y - 1][x][i] + 1;
    }
    for (let y = size - 2; y >= 0; --y) {
      for (let i = 0; i <= grid[y + 1][x]; ++i) south[y][x][i] = 1;
      for (let i = grid[y + 1][x] + 1; i < 10; ++i) south[y][x][i] = south[y + 1][x][i] + 1;
    }
  }

  const west = initMask();
  const east = initMask();
  for (let y = 0; y < size; ++y) {
    for (let x = 1; x < size; ++x) {
      for (let i = 0; i <= grid[y][x - 1]; ++i) west[y][x][i] = 1;
      for (let i = grid[y][x - 1] + 1; i < 10; ++i) west[y][x][i] = west[y][x - 1][i] + 1;
    }
    for (let x = size - 2; x >= 0; --x) {
      for (let i = 0; i <= grid[y][x + 1]; ++i) east[y][x][i] = 1;
      for (let i = grid[y][x + 1] + 1; i < 10; ++i) east[y][x][i] = east[y][x + 1][i] + 1;
    }
  }

  let solution = 0;
  for (let y = 0; y < size; ++y) {
    for (let x = 0; x < size; ++x) {
      const i = grid[y][x];
      solution = Math.max(
        solution,
        north[y][x][i] * south[y][x][i] * west[y][x][i] * east[y][x][i]
      );
    }
  }
  return solution;
}


function loadGrid(filePath) {
  const grid = fs.readFileSync(filePath, 'utf8')
    .trim()
    .split(/\n/)
    .map(r => r.split('').map(x => parseInt(x)));

  const size = grid.length;
  assert(size === grid[0].length);

  return {'grid': grid, 'size': size};
}


process.argv.slice(2).forEach(solve);
