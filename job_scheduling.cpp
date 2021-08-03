#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void print_vect_vect( vector<vector<double>> v){
    int len = v.size();
    for (int i=0; i<len; i++){
        cout<<v[i][0]<<','<<v[i][1]<<endl;
    }
}

void print_vect( vector<double> v){
    int len = v.size();
    for (int i=0; i<len; i++){
        cout<<v[i]<<endl;
    }
}


bool comp_schedule(const vector<double>& a, const vector<double>& b){
    if(a[0]==b[0]){
        return (a[1]>b[1]);
    }
    return (a[0]>b[0]);
}

class JobScheduling{

    public:
        string file_address;
        int num_of_jobs; 
        vector<vector<double>> jobs;
        vector<vector<double>> job_diff;
        vector<vector<double>> job_ratio;

        void read_jobs_file(string file_address, vector<vector<double>> &jobs){
            ifstream infile;
            string row;
            double job_weight;
            double job_len;
            double length=0;
            infile.open(file_address);
            infile>>num_of_jobs;
            getline(infile,row);

            while(infile.good()){
                getline(infile,row);
                stringstream s(row);
                s>>job_weight;
                s>>job_len;
                length = length+job_len;
                vector<double> new_job = {job_weight,job_len};
                jobs.push_back(new_job);
            }
        }

        void set_jobs_diff(vector<vector<double>> &jobs, vector<vector<double>> &job_diff){
            vector<double> init = {0.0,0.0,0.0};
            job_diff.resize(num_of_jobs,init);
            for (int i=0; i<num_of_jobs; i++){
                job_diff[i][0] = jobs[i][0]-jobs[i][1];
                job_diff[i][1] = jobs[i][0];
                job_diff[i][2] = i;
            }       
        }

        void set_jobs_ratio(vector<vector<double>> &jobs, vector<vector<double>> &job_ratio){
            vector<double> init = {0.0,0.0,0.0};
            job_ratio.resize(num_of_jobs,init);
            for (int i=0; i<num_of_jobs; i++){
                job_ratio[i][0] = jobs[i][0]/jobs[i][1];
                job_ratio[i][2] = jobs[i][0];
                job_ratio[i][2] = i;
            }
        }       

        int schedule_diff(vector<vector<double>> &jobs, vector<vector<double>> &job_diff){
            int len = num_of_jobs;
            double ans = 0;
            double finish_time = 0;
            sort(job_diff.begin(),job_diff.end(),comp_schedule);

            for (int i=0; i<len; i++){
                int ind = job_diff[i][2];
                double weight = jobs[ind][0];
                double length = jobs[ind][1];
                finish_time = finish_time+length;
                ans = ans + finish_time*weight;
            }
            cout<<ans<<endl;
            cout<<finish_time<<endl;
            return ans;
        }

        int schedule_ratio(vector<vector<double>> &jobs, vector<vector<double>> &job_ratio){
            int len = num_of_jobs;
            double ans = 0;
            double finish_time = 0;
            sort(job_ratio.begin(),job_ratio.end(),comp_schedule);

            for (int i=0; i<len; i++){
                int ind = job_ratio[i][2];
                double weight = jobs[ind][0];
                double length = jobs[ind][1];
                finish_time = finish_time+length;
                ans = ans + finish_time*weight;
            }
            cout<<ans<<endl;
            cout<<finish_time<<endl;
            return ans;
        }


        JobScheduling(string file_add){
            file_address = file_add;
            read_jobs_file(file_address, jobs);
            set_jobs_diff(jobs,job_diff);
            set_jobs_ratio(jobs,job_ratio);
            schedule_diff(jobs,job_diff);
            schedule_ratio(jobs,job_ratio);
        }

};

int main(){
    cout.precision(100);
    string file_address = "G:\\My Drive\\course\\Algorithm\\Job Scheduling\\jobs.txt";
    JobScheduling js(file_address);
    return 0;
}