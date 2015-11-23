#ifndef QS_RES_HPP
#define QS_RES_HPP

#include "QsQuery.hpp"
#include <vector>

using std::vector;


struct ResultCl {

        int total;
        int accepted;
        int rejected;

        double p_rej;

        double mean_t_wait;
        double mean_t_proc;
        double mean_t_resid;

        double disp_t_wait;
        double disp_t_proc;

        ResultCl();

};

struct ResultSrv {

    double k_usage;
    double full_time_processing;
    double work_time;
    ResultSrv();
};



class QsRes {




public:


    static vector<QsQuery*>* acceptedByClient;
    static vector<QsQuery*>* acceptedByServer;
    static vector<QsQuery*>* rejectedByClient;
    static ResultCl* sumInfoByClient;
    static ResultSrv* sumInfoByServer;


    static int CURR_ACCEPTED;

    QsRes();
    ~QsRes();
    static void addToAccepted(QsQuery*);
    static void addToRejected(QsQuery*);
    static void calculateSummaryInfo();

};


#endif // QS_RES_HPP
