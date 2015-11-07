//     _    ____  _  __
//    / \  / ___|| |/ /  ASK
//   / _ \ \___ \| ' /   Authentication Sessions Keeper Server
//  / ___ \ ___) | . \   -------------------------------------
// /_/   \_\____/|_|\_\  www.codegazoline.it/ask
//                 v1.0
// ===============================================================================
// Copyright (C) 2015, Luca Stasio - joshuagame@gmail.com //The CodeGazoline Team/
//
// main.c
// main entry point for the ASK Server
//
// This file is part of the ASK Server.
//
// The ASK Server is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// The ASK Server is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Nome - Programma.If not, see <http://www.gnu.org/licenses/>.

#include "ASKServer.h"

int main(int argc, char** argv)
{
    askeeper::server::ASKServer server;
    return server.run(argc, argv);
}