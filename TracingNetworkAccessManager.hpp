#pragma once
#include <QNetworkAccessManager>
#include <stdio.h>

class TracingNetworkAccessManager : public QNetworkAccessManager {
public:
	TracingNetworkAccessManager() : m_tracefile(NULL) {}
	void enableConnectionTrace(FILE *output) { m_tracefile = output; }

protected:
	virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData = 0)
	{
		if (m_tracefile)
			fprintf(m_tracefile, "%s\n", request.url().toString().toUtf8().constData());
		return QNetworkAccessManager::createRequest(op, request, outgoingData);
	}

private:
	FILE *m_tracefile;
};

