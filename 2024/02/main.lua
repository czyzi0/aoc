local SOLUTIONS_PART1 = {
    ["sample1.txt"] = 2,
    ["input.txt"] = 402,
}
local SOLUTIONS_PART2 = {
    ["sample1.txt"] = 4,
    ["input.txt"] = 455,
}


local function load_reports(file_path)
    local reports = {}
    for report_ in io.lines(file_path) do
        local report = {}
        for num in string.gmatch(report_, "%d+") do
            table.insert(report, tonumber(num))
        end
        table.insert(reports, report)
    end
    return reports
end


local function is_report_safe (report)
    local safe, last_diff = true, nil
    for i = 2, #report do
        local diff = report[i] - report[i - 1]
        if diff == 0 or math.abs(diff) > 3 or last_diff and diff * last_diff < 0 then
            safe = false
            break
        end
        last_diff = diff
    end
    return safe
end


local function solve_part1(file_path)
    local result = 0
    for _, report in ipairs(load_reports(file_path)) do
        if is_report_safe(report) then
            result = result + 1
        end
    end
    return result
end


local function solve_part2(file_path)
    local result = 0
    for _, report in ipairs(load_reports(file_path)) do
        if is_report_safe(report) then
            result = result + 1
        else
            for i = 1, #report do
                local level = table.remove(report, i)
                if is_report_safe(report) then
                    result = result + 1
                    break
                end
                table.insert(report, i, level)
            end
        end
    end
    return result
end


local function solve(file_path)
    local file_name = string.match(file_path, ".*/([^/]+)")
    print("### " .. file_name .. " ###")

    if SOLUTIONS_PART1[file_name] ~= nil then
        local solution_part1_ = solve_part1(file_path)
        print("Part1: " .. solution_part1_)
        local solution_part1 = SOLUTIONS_PART1[file_name]
        assert(solution_part1_ == solution_part1)
    end

    if SOLUTIONS_PART2[file_name] ~= nil then
        local solution_part2_ = solve_part2(file_path)
        print("Part2: " .. solution_part2_)
        local solution_part2 = SOLUTIONS_PART2[file_name]
        assert(solution_part2_ == solution_part2)
    end
end


for _, file_path in ipairs(arg) do
    solve(file_path)
end
