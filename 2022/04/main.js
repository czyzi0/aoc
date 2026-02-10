const assert = require('assert');
const fs = require('fs');
const path = require('path');


const SOLUTIONS_PART1 = {
  'sample1.txt': 2,
  'input.txt': 464,
};
const SOLUTIONS_PART2 = {
  'sample1.txt': 4,
  'input.txt': 770,
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
    assert(solutionPart2_ === solutionPart2);
  }
}


function solvePart1(filePath) {
  let solution = 0;
  for (const [aLo, aHi, bLo, bHi] of loadRanges(filePath)) {
    if (aLo <= bLo && aHi >= bHi) solution += 1;
    else if (aLo >= bLo && aHi <= bHi) solution += 1;
  }
  return solution;
}


function solvePart2(filePath) {
  let solution = 0;
  for (const [aLo, aHi, bLo, bHi] of loadRanges(filePath)) {
    if (bLo <= aHi && bHi >= aLo) solution += 1;
  }
  return solution;
}


function loadRanges(filePath) {
  return fs.readFileSync(filePath, 'utf8')
    .trim()
    .split(/\n/)
    .map(l => l.split(',')
      .map(x => x.split('-'))
      .flat()
      .map(x => parseInt(x))
    );
}


process.argv.slice(2).forEach(solve);
