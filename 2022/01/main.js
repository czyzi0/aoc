const assert = require('assert');
const fs = require('fs');


const SOLUTIONS_PART1 = {
  'sample1.txt': 24000,
  'input.txt': 68802,
};
const SOLUTIONS_PART2 = {
  'sample1.txt': 45000,
  'input.txt': 205370,
};


function solve(filePath) {
  console.log(filePath)

  if (filePath in SOLUTIONS_PART1) {
    const solutionPart1_ = solvePart1(filePath);
    console.log(`Part 1: ${solutionPart1_}`);
    const solutionPart1 = SOLUTIONS_PART1[filePath];
    assert(solutionPart1_ == solutionPart1);
  }

  if (filePath in SOLUTIONS_PART2) {
    const solutionPart2_ = solvePart2(filePath);
    console.log(`Part 2: ${solutionPart2_}`);
    const solutionPart2 = SOLUTIONS_PART2[filePath];
    assert(solutionPart2_ == solutionPart2);
  }

  console.log('-'.repeat(40));
}


function solvePart1(filePath) {
  return Math.max(...loadKcal(filePath));
}


function solvePart2(filePath) {
  const kcal = loadKcal(filePath);
  kcal.sort((a, b) => { return b - a });
  return kcal.slice(0, 3).reduce((a, b) => a + b, 0);
}


function loadKcal(filePath) {
  const lines = fs.readFileSync(filePath, 'utf8').split(/\n/);
  const kcal = new Array(1).fill(0);
  for (const line of lines) {
    if (line === '') {
      kcal.push(0);
    } else {
      kcal[kcal.length - 1] += parseInt(line);
    }
  }
  kcal.pop();
  return kcal;
}


process.argv.slice(2).forEach(solve);
