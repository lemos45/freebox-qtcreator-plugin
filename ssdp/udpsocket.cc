/*
  Freebox QtCreator plugin for QML application development.

  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not see
  http://www.gnu.org/licenses/lgpl-2.1.html.

  Copyright (c) 2014, Freebox SAS, See AUTHORS for details.
*/

#include "udpsocket.hh"

#include <QNetworkProxy>

namespace Freebox {
namespace Ssdp {

UdpSocket::UdpSocket(QObject *parent) :
    QUdpSocket(parent)
{
    setProxy(QNetworkProxy::NoProxy);
    connect(this, SIGNAL(readyRead()), SLOT(datagramRead()));
}

void UdpSocket::datagramRead()
{
    while (hasPendingDatagrams()) {
        QByteArray data;
        QHostAddress from;

        data.resize(pendingDatagramSize());

        readDatagram(data.data(), data.size(), &from);

        emit datagramReceived(from, data);
    }
}

} // namespace Ssdp
} // namespace Freebox
