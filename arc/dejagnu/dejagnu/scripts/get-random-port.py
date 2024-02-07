#!/usr/bin/env python3

# Copyright (C) 2024 Synopsys Inc.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 3 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.

import random
import socket
from contextlib import closing

MIN_PORT_NUMBER = 10000
MAX_PORT_NUMBER = 30000


def port_available(port: int) -> bool:
    with closing(socket.socket(socket.AF_INET, socket.SOCK_STREAM)) as sock:
        return sock.connect_ex(('127.0.0.1', port)) != 0


def get_random_available_port() -> int:
    while True:
        port = random.randint(MIN_PORT_NUMBER, MAX_PORT_NUMBER)
        if port_available(port):
            return port


if __name__ == '__main__':
    print(get_random_available_port())
