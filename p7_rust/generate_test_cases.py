import random

def generate_test_cases(num_instances, num_jobs_range, start_time_range, end_time_range, weight_range):
    """
    Generate test cases for job scheduling.

    Parameters:
    - num_instances: Number of instances to generate.
    - num_jobs_range: Tuple of (min, max) for the number of jobs per instance.
    - start_time_range: Tuple of (min, max) for the job start time.
    - end_time_range: Tuple of (min, max) for the job end time.
    - weight_range: Tuple of (min, max) for the job weight.
    """

    print(num_instances)

    for _ in range(int(num_instances)):
        num_jobs = random.randint(int(num_jobs_range[0]), int(num_jobs_range[1]))

        print(num_jobs)
        
        for _ in range(num_jobs):
            start_time = random.randint(int(start_time_range[0]), int(start_time_range[1]))
            end_time = random.randint(int(end_time_range[0]), int(end_time_range[1]))
            weight = random.randint(int(weight_range[0]), int(weight_range[1]))
            
            # Ensure end_time > start_time, if not, swap or adjust them
            if end_time <= start_time:
                end_time = start_time + 1
            
            print(f"{start_time} {end_time} {weight}")

# Example usage:
# Generate 3 instances.
# Each instance will have between 5 to 10 jobs.
# Start time between 1 and 100, end time between 2 and 200, weight between 1 and 50.
generate_test_cases(
    num_instances=10,
    num_jobs_range=(1e5, 1e6),
    start_time_range=(1, 1e5),
    end_time_range=(2, 1e5),
    weight_range=(1, 1e5)
)
