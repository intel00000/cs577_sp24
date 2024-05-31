use std::io::{self, BufRead};

// A structure to represent a job
struct Job {
    weight: usize,
    value: usize,
}

// knapsack problem
fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines().map(|x| x.unwrap());

    // scan the first line from stdin to get the number of instances
    let num_instances: usize = lines.next().unwrap().parse().unwrap();

    for _ in 0..num_instances {
        // scan the line to get number of items and capacity in the same line as format "num_items capacity"
        let instance_line = lines.next().unwrap();
        let mut instance_line_iter = instance_line.split_whitespace();
        let num_items: usize = instance_line_iter.next().unwrap().parse().unwrap();
        let capacity: usize = instance_line_iter.next().unwrap().parse().unwrap();

        // init an array of jobs
        let mut jobs: Vec<Job> = Vec::with_capacity(num_items);
        // read the jobs from stdin
        for _ in 0..num_items {
            let job_line = lines.next().unwrap();
            let mut job_line_iter = job_line.split_whitespace();
            let weight: usize = job_line_iter.next().unwrap().parse().unwrap();
            let value: usize = job_line_iter.next().unwrap().parse().unwrap();
            jobs.push(Job { weight, value });
        }

        // create a 2D array to store the maximum value that can be obtained for each item and each weight
        // to save memory, we only keep the latest two rows
        // no need to pre-fill the array with 0s as the default value of a Vec is 0
        let mut dp: Vec<Vec<usize>> = vec![vec![0; capacity + 1]; 2];

        // fill the dp array
        for i in 1..=num_items {
            let actual_i = i % 2;
            for j in 1..=capacity {
                if jobs[i - 1].weight <= j {
                    dp[actual_i][j] = dp[1 - actual_i][j - jobs[i - 1].weight] + jobs[i - 1].value;
                    if dp[1 - actual_i][j] > dp[actual_i][j] {
                        dp[actual_i][j] = dp[1 - actual_i][j];
                    }
                } else {
                    dp[actual_i][j] = dp[1 - actual_i][j];
                }
            }
        }

        // Print the maximum value that can be obtained
        println!("{}", dp[num_items % 2][capacity]);
    }
}
