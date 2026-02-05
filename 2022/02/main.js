const assert = require('assert');
const fs = require('fs');
const path = require('path');


const SOLUTIONS_PART1 = {
  'sample1.txt': 15,
  'input.txt': 13221,
};
const SOLUTIONS_PART2 = {
  'sample1.txt': 12,
  'input.txt': 13131,
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
  const lines = fs.readFileSync(filePath, 'utf8').split(/\n/);
  let solution = 0;

  for (let line of lines) {
    if (!line) continue;

    if (line.endsWith("X")) solution += 1;
    else if (line.endsWith("Y")) solution += 2;
    else if (line.endsWith("Z")) solution += 3;
    else assert(false);

    if (["A Z", "B X", "C Y"].includes(line)) solution += 0;
    else if (["A X", "B Y", "C Z"].includes(line)) solution += 3;
    else if (["A Y", "B Z", "C X"].includes(line)) solution += 6;
    else assert(false);
  }

  return solution;
}


function solvePart2(filePath) {
  const lines = fs.readFileSync(filePath, 'utf8').split(/\n/);
  let solution = 0;

  for (let line of lines) {
    if (!line) continue;

    if (["A Y", "B X", "C Z"].includes(line)) solution += 1;
    else if (["A Z", "B Y", "C X"].includes(line)) solution += 2;
    else if (["A X", "B Z", "C Y"].includes(line)) solution += 3;
    else assert(false);

    if (line.endsWith("X")) solution += 0;
    else if (line.endsWith("Y")) solution += 3;
    else if (line.endsWith("Z")) solution += 6;
    else assert(false);
  }

  return solution;
}


process.argv.slice(2).forEach(solve);
