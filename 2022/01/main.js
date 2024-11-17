const assert = require('assert');
const fs = require('fs');
const path = require('path');


const SOLUTIONS_PART1 = {
  'sample1.txt': 24000,
  'input.txt': 68802,
};
const SOLUTIONS_PART2 = {
  'sample1.txt': 45000,
  'input.txt': 205370,
};


function solve(filePath) {
  const fileName = path.basename(filePath)
  console.log(`### ${fileName} ###`)

  if (fileName in SOLUTIONS_PART1) {
    const solutionPart1_ = solvePart1(filePath);
    console.log(`Part 1: ${solutionPart1_}`);
    const solutionPart1 = SOLUTIONS_PART1[fileName];
    assert(solutionPart1_ == solutionPart1);
  }

  if (fileName in SOLUTIONS_PART2) {
    const solutionPart2_ = solvePart2(filePath);
    console.log(`Part 2: ${solutionPart2_}`);
    const solutionPart2 = SOLUTIONS_PART2[fileName];
    assert(solutionPart2_ == solutionPart2);
  }
}


function solvePart1(filePath) {
  return Math.max(...loadKcal(filePath));
}


function solvePart2(filePath) {
  return loadKcal(filePath).sort((a, b) => { return b - a }).slice(0, 3).reduce((a, b) => a + b, 0);
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
