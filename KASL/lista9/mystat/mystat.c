#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>

#define DEFAULT_PERIOD 1
#define DEFAULT_INTERVAL 60
#define DEFAULT_LOGFILE "/var/log/mystat.log"

typedef struct {
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
} CpuStat;

int read_cpu_usage(CpuStat *stat) {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) return -1;

    char buffer[256];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);

    sscanf(buffer, "cpu  %llu %llu %llu %llu %llu %llu %llu %llu",
           &stat->user, &stat->nice, &stat->system, &stat->idle,
           &stat->iowait, &stat->irq, &stat->softirq, &stat->steal);
    return 0;
}

double calculate_usage(CpuStat *prev, CpuStat *curr) {
    unsigned long long prev_idle = prev->idle + prev->iowait;
    unsigned long long curr_idle = curr->idle + curr->iowait;

    unsigned long long prev_non_idle = prev->user + prev->nice + prev->system +
                                       prev->irq + prev->softirq + prev->steal;
    unsigned long long curr_non_idle = curr->user + curr->nice + curr->system +
                                       curr->irq + curr->softirq + curr->steal;

    unsigned long long prev_total = prev_idle + prev_non_idle;
    unsigned long long curr_total = curr_idle + curr_non_idle;

    double total_diff = (double)(curr_total - prev_total);
    double idle_diff = (double)(curr_idle - prev_idle);

    return (total_diff - idle_diff) / total_diff * 100.0;
}

int main(int argc, char *argv[]) {
    int period = DEFAULT_PERIOD;
    int interval = DEFAULT_INTERVAL;
    const char *logfile = DEFAULT_LOGFILE;

    static struct option long_options[] = {
        {"period", required_argument, 0, 'p'},
        {"interval", required_argument, 0, 'i'},
        {"logfile", required_argument, 0, 'f'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "p:i:f:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'p': period = atoi(optarg); break;
            case 'i': interval = atoi(optarg); break;
            case 'f': logfile = optarg; break;
            default:
                fprintf(stderr, "Usage: %s [-p period] [-i interval] [-f logfile]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    int count = 0;
    double sum = 0.0, min = 100.0, max = 0.0;
    CpuStat prev, curr;

    read_cpu_usage(&prev);
    sleep(period);

    while (1) {
        read_cpu_usage(&curr);
        double usage = calculate_usage(&prev, &curr);

        if (usage < min) min = usage;
        if (usage > max) max = usage;
        sum += usage;
        count++;

        if ((count * period) >= interval) {
            FILE *fp = fopen(logfile, "a");

            char buf[64];
            time_t t = time(NULL);
            struct tm *tm_info = localtime(&t);
            strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);

            if (fp) {
                time_t now = time(NULL);
                fprintf(fp, "[%s] AVG: %.2f%%, MIN: %.2f%%, MAX: %.2f%%\n",
                        buf, sum / count, min, max);
                fclose(fp);
            }
            sum = 0.0;
            min = 100.0;
            max = 0.0;
            count = 0;
        }

        prev = curr;
        sleep(period);
    }

    return 0;
}
