#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <iostream>
#include <locale.h>
#include <exception>

// define task type
enum Task{
    DOWN_SHARE_HISTORY, //to crawl all share's history data in market,
    SYNC_ALL_SHARE, // sync all share data to newest
    WATCH_SHARE, // watch favorite share's newest price, if share price make a breakthrough, notify user
    ANALYSIS_SHARE, // analysis shares after market close
};

#endif // GLOBAL_H_INCLUDED
