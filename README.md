# Scheduling

This file describes a set of jobs with positive and integral weights and lengths. It has the format

[number_of_jobs]

[job_1_weight] [job_1_length]

[job_2_weight] [job_2_length]


The code implements the greedy algorithm that schedules jobs in decreasing order of the difference (weight - length). Also it implements the greedy algorithm that schedules 
jobs (optimally) in decreasing order of the ratio (weight/length).
