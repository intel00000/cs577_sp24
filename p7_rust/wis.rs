use std::io;

struct Job {
    start: i32,
    end: i32,
    weight: i32,
}

// using binary search to find the latest non-overlapping job
fn find_latest_non_overlapping_job(jobs: &[Job], index: usize) -> isize {
    let mut low: isize = 0;
    let mut high: isize = index as isize - 1;

    while low <= high {
        let mid = (low + high) / 2;
        if jobs[mid as usize].end <= jobs[index].start {
            if mid == index as isize - 1 || jobs[(mid + 1) as usize].end > jobs[index].start {
                return mid;
            }
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    -1
}

fn main() {
    let stdin = io::stdin();

    // read number of instances
    let mut input = String::new();
    stdin.read_line(&mut input).unwrap();
    let num_instances: i32 = input.trim().parse().unwrap();

    for _ in 0..num_instances {
        // read number of jobs
        let mut input = String::new();
        stdin.read_line(&mut input).unwrap();
        let num_jobs: i32 = input.trim().parse().unwrap();

        let mut jobs: Vec<Job> = Vec::with_capacity(num_jobs);
        for _ in 0..num_jobs {
            let mut job_input = String::new();
            stdin.read_line(&mut job_input).unwrap();
            let job_data: Vec<i32> = job_input
                .split_whitespace()
                .map(|x| x.parse().unwrap())
                .collect();
            jobs.push(Job {
                start: job_data[0],
                end: job_data[1],
                weight: job_data[2],
            });
        }

        // sort jobs by end time
        jobs.sort_by(|a, b| a.end.cmp(&b.end));

        // create an array to store max weight to avoid recomputation
        let mut max_weight_array = vec![0u64; num_jobs + 1];

        for i in 1..=num_jobs {
            let incl_weight = jobs[i - 1].weight as u64;
            let l = find_latest_non_overlapping_job(&jobs, i - 1);
            let incl_weight = if l != -1 { incl_weight + max_weight_array[l as usize + 1] } else { incl_weight };

            max_weight_array[i] = std::cmp::max(incl_weight, max_weight_array[i - 1]);
        }

        println!("{}", max_weight_array[num_jobs]);
    }
}