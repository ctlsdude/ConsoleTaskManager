#include "iomanip"
#include "TaskScanner.h"

TaskContainer TaskScanner::scanTasks(std::string pathToFile) {

    TaskContainer tasks;
    try{

        rapidcsv::Document doc(pathToFile, rapidcsv::LabelParams(0, -1));
        int taskNumber = doc.GetRowCount();

        for(int i = 0; i < taskNumber; i++) {

            std::vector<std::string> row = doc.GetRow<std::string>(i);
            //!!!
            struct std::tm createTime{};
            std::string date = row[2];
            std::istringstream ss(date);
            ss >> std::get_time(&createTime, "%Y-%m-%d %H:%M");

            TaskStatus status =  UNDONE;
            if (row[3] == "OFF") status = DONE;

            tasks.addTask( Task(row[0], createTime, row[1], row[3], status) );
        }
        return tasks;
    }
    catch ( std::ios_base::failure ) {

        std::cerr << "ConsoleTaskManager: Error opening file with tasks";
        return tasks;
    }
}

bool TaskScanner::writeTasksToFile(TaskContainer tasks, std::string pathToFile) {

    std::ofstream fileStream;
    try {

        fileStream.open(pathToFile); // окрываем файл для записи
        if ( fileStream.is_open() )
        {
            fileStream << "Name,Description,Date,Category,Status"  << std::endl;
            auto tasksMap = tasks.getRefToTasks();
            for(const auto & it : tasksMap) {
                fileStream << it.second.getAllAboutTask()  << std::endl;
            }
            return true;
        }
    }
    catch (std::ios_base::failure) {

        std::cerr << "ConsoleTaskManager: Error opening file for tasks";
    }
    return false;
}
