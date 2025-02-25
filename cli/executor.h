/*
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2022 Cppcheck team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <cstddef>
#include <list>
#include <map>
#include <mutex>
#include <string>

class Settings;
class ErrorLogger;
class ErrorMessage;

/// @addtogroup CLI
/// @{

/**
 * This class will take a list of filenames and settings and check then
 * all files using threads.
 */
class Executor {
public:
    Executor(const std::map<std::string, std::size_t> &files, Settings &settings, ErrorLogger &errorLogger);
    virtual ~Executor();

    Executor(const Executor &) = delete;
    void operator=(const Executor &) = delete;

    virtual unsigned int check() = 0;

protected:
    /**
     * @brief Check if message is being suppressed and unique.
     * @param msg the message to check
     * @return true if message is not suppressed and unique
     */
    bool hasToLog(const ErrorMessage &msg);

    const std::map<std::string, std::size_t> &mFiles;
    Settings &mSettings;
    ErrorLogger &mErrorLogger;

private:
    std::mutex mErrorListSync;
    std::list<std::string> mErrorList;
};

/// @}

#endif // EXECUTOR_H
