#include "QsRes.hpp"
#include "QsSettings.hpp"

#include <QDebug>

inline long double sqr(long double x) {
    return (x) * (x);
}

ResultCl::ResultCl() {

    mean_t_wait = 0;
    mean_t_proc = 0;
    mean_t_resid = 0;
    p_rej = 0;
    accepted = 0;
    rejected = 0;
    total = 0;
    disp_t_wait = 0;
    disp_t_proc = 0;

}


ResultSrv::ResultSrv() {

    k_usage = 0;
    work_time = 0;
    full_time_processing = 0;

}


vector<QsQuery*>* QsRes::acceptedByClient = nullptr;
vector<QsQuery*>* QsRes::acceptedByServer = nullptr;
vector<QsQuery*>* QsRes::rejectedByClient = nullptr;
ResultCl* QsRes::sumInfoByClient = nullptr;
ResultSrv* QsRes::sumInfoByServer = nullptr;
int QsRes::CURR_ACCEPTED = 0;



QsRes::QsRes() {

    acceptedByClient = new std::vector<QsQuery*> [QsSettings::C];
    acceptedByServer = new std::vector<QsQuery*> [QsSettings::S];
    rejectedByClient = new std::vector<QsQuery*> [QsSettings::C];
    sumInfoByClient = new ResultCl [QsSettings::C];
    sumInfoByServer = new ResultSrv [QsSettings::S];
    CURR_ACCEPTED = 0;

}

QsRes::~QsRes()
{

   delete [] acceptedByClient;
   delete [] rejectedByClient;
   delete [] acceptedByServer;
   delete [] sumInfoByClient;
   delete [] sumInfoByServer;
}

void QsRes::addToAccepted(QsQuery* query) {

    int c = query->id_client - 1;
    acceptedByClient[c].push_back(query);
    int s = query->id_server - 1;
    acceptedByServer[s].push_back(query);

    ++CURR_ACCEPTED;
}


void QsRes::addToRejected(QsQuery* query) {

    int c = query->id_client - 1;
    rejectedByClient[c].push_back(query);
}





void QsRes::calculateSummaryInfo() {

   for(int c = 0; c < QsSettings::C; ++c) {

        auto& acc = acceptedByClient[c]; //
        auto& rej = rejectedByClient[c]; // <-- aliases
        auto& info = sumInfoByClient[c]; //

        info.accepted = acc.size();
        info.rejected = rej.size();
        info.total = info.accepted + info.rejected;

        double sum_t_wait = 0; double sum_t_proc = 0;
        for (const auto& qu : acc) {
            sum_t_wait += (qu->timeWaitingOut - qu->timeWaitingIn);
            sum_t_proc += (qu->finalizingTime - qu->timeWaitingOut);
        }

        info.mean_t_wait = sum_t_wait / info.accepted;
        info.mean_t_proc = sum_t_proc / info.accepted;
        info.mean_t_resid = info.mean_t_wait + info.mean_t_proc;

        double sqr_sum_t_wait = 0; double sqr_sum_t_proc = 0;
        for (const auto& qu : acc) {
            sqr_sum_t_wait += sqr(qu->timeWaitingOut - qu->timeWaitingIn) - sqr(info.mean_t_wait);
            sqr_sum_t_proc += sqr(qu->finalizingTime - qu->timeWaitingOut) - sqr(info.mean_t_proc);
        }

        info.disp_t_wait = sqr_sum_t_wait / info.accepted;
        info.disp_t_proc = sqr_sum_t_proc / info.accepted;

        info.p_rej = double(info.rejected) / info.total;



   }


    for(int s = 0; s < QsSettings::S; ++s ) {

        auto& queries = acceptedByServer[s];
        auto& info = sumInfoByServer[s];

        for (const auto& qu : queries) {
            info.full_time_processing += (qu->finalizingTime - qu->timeWaitingOut);
            info.work_time = qu->finalizingTime;  // <-- this is govnokod
        }

        info.k_usage = info.full_time_processing / info.work_time;

    }



}




