#ifndef HISTORY_H
#define HISTORY_H

#include <queue>
#include <QImage>
#include "Action.h"

class History
{
    friend class MainWindow;

public:

    struct Entry {
        Entry() {};
        Action act;
        QImage prevImg;

        bool isNull() const
        {
            return prevImg.isNull();
        }
    };

    static History & get()
    {
        static History hist;
        return hist;
    }

public:
    void setMax(int m = 10)
    {
        maxHistory = m;
    }

    void add(Action * act, QImage img)
    {
        Entry ent;
        ent.act = *act;
        ent.prevImg = img;

        redoHistory.clear();
        undoHistory.push_back(ent);
        if(undoHistory.size() > maxHistory) undoHistory.pop_front();
    }

    Entry undo(QImage & cImg)
    {
        if (undoHistory.size() <= 0) return Entry();

        Entry ent = undoHistory[undoHistory.size()-1];
        redoHistory.push_back(ent);
        redoHistory.back().prevImg = cImg;
        undoHistory.pop_back();
        return ent;
    }

    Entry redo(QImage & cImg)
    {
        if (redoHistory.size() <= 0) return Entry();

        Entry ent = redoHistory[redoHistory.size()-1];
        undoHistory.push_back(ent);
        undoHistory.back().prevImg = cImg;
        redoHistory.pop_back();
        return ent;
    }



protected:
    std::deque<Entry> undoHistory;
    std::deque<Entry> redoHistory;

    unsigned int maxHistory = 10;

protected:
    History() {};
};

#endif // HISTORY_H
