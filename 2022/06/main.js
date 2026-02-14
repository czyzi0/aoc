const assert = require('assert');
const fs = require('fs');
const path = require('path');


const SOLUTIONS_PART1 = {
  'sample1.txt': 7,
  'sample2.txt': 5,
  'sample3.txt': 6,
  'sample4.txt': 10,
  'sample5.txt': 11,
  'input.txt': 1804,
};
const SOLUTIONS_PART2 = {
  'sample1.txt': 19,
  'sample2.txt': 23,
  'sample3.txt': 23,
  'sample4.txt': 29,
  'sample5.txt': 26,
  'input.txt': 2508,
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
  return solveForPacketSize(filePath, 4);
}


function solvePart2(filePath) {
  return solveForPacketSize(filePath, 14);
}


function solveForPacketSize(filePath, packetSize) {
  const signal = fs.readFileSync(filePath, 'utf8').trim();
  for (let i = packetSize; i < signal.length; ++i) {
    const packet = new Set(signal.slice(i - packetSize, i));
    if (packet.size === packetSize) return i;
  }
}


process.argv.slice(2).forEach(solve);
