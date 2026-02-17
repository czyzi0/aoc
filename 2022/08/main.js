const assert = require('assert');
const fs = require('fs');
const path = require('path');


const SOLUTIONS_PART1 = {
  'sample1.txt': 21,
  'input.txt': 1698,
};
const SOLUTIONS_PART2 = {
  'sample1.txt': 0,
  'input.txt': 0,
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

  // if (fileName in SOLUTIONS_PART2) {
  //   const solutionPart2_ = solvePart2(filePath);
  //   console.log(`Part 2: ${solutionPart2_}`);
  //   const solutionPart2 = SOLUTIONS_PART2[fileName];
  //   assert(solutionPart2_ === solutionPart2);
  // }
}


function solvePart1(filePath) {
  const grid = fs.readFileSync(filePath, 'utf8')
    .trim()
    .split(/\n/)
    .map(r => r.split('').map(x => parseInt(x)));
  const size = grid.length; assert(size === grid[0].length);

  const north = Array(size).fill().map(() => Array(size).fill(-1));
  const south = Array(size).fill().map(() => Array(size).fill(-1));
  for (let x = 0; x < size; ++x) {
    for (let y = 1; y < size; ++y)
      north[y][x] = Math.max(north[y - 1][x], grid[y - 1][x]);
    for (let y = size - 2; y >= 0; --y)
      south[y][x] = Math.max(south[y + 1][x], grid[y + 1][x]);
  }

  const west = Array(size).fill().map(() => Array(size).fill(-1));
  const east = Array(size).fill().map(() => Array(size).fill(-1));
  for (let y = 0; y < size; ++y) {
    for (let x = 1; x < size; ++x)
      west[y][x] = Math.max(west[y][x - 1], grid[y][x - 1]);
    for (let x = size - 2; x >= 0; --x)
      east[y][x] = Math.max(east[y][x + 1], grid[y][x + 1]);
  }

  let nVisible = 0;
  for (let y = 0; y < size; ++y)
    for (let x = 0; x < size; ++x)
      nVisible += grid[y][x] > Math.min(north[y][x], south[y][x], west[y][x], east[y][x]);
  return nVisible;
}


// function solvePart2(filePath) {
// }


process.argv.slice(2).forEach(solve);
