/*
 * GNetworking.h
 *
 *  Created on: 01/08/2014
 *      Author: a.sabo
 */

/**
 * http://stackoverflow.com/questions/20957727/boostasio-unregisterwaitex-has-not-been-declared

For eclipse, add symbol: _WIN32_WINNT val: 0x0601 (or for your windows system: http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745%28v=vs.85%29.aspx) to resolve the primary issue.

The WSAPOLLFD issue is due to: https://github.com/mozilla/rust/issues/9246 && http://sourceforge.net/p/mingw/bugs/2049/ which is patched by adding:

typedef struct pollfd {
  SOCKET fd;
  short  events;
  short  revents;
} WSAPOLLFD, *PWSAPOLLFD, *LPWSAPOLLFD;
to winsock2.h.

 */
#ifndef GNETWORKING_H_
#define GNETWORKING_H_

#include <string>
#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include <tr1/functional>

using boost::asio::ip::udp;

namespace Acsabo {

class GNetworking {
private:
	enum TYPE {LOGIN, QUIT, UPDATE, MESSAGE};

	std::string appz;
	std::string usr;
	std::string pwd;
	std::string userName;

	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint sender_endpoint_;

	enum {
		max_length = 1024
	};
	char data_[max_length];

	const short multicast_port = 4446;

	//SENDER
	boost::asio::io_service* io_service;

	boost::asio::io_service* service;

	udp::socket* s;
	udp::resolver::iterator* iterator;

	GNetworking(boost::asio::io_service& io_service,
			const boost::asio::ip::address& listen_address,
			const boost::asio::ip::address& multicast_address) :
			socket_(io_service) {

		this->io_service = &io_service;
		// Create the socket so that multiple may be bound to the same address.
		boost::asio::ip::udp::endpoint listen_endpoint(listen_address,
				multicast_port);
		socket_.open(listen_endpoint.protocol());
		socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
		socket_.bind(listen_endpoint);

		// Join the multicast group.
		socket_.set_option(
				boost::asio::ip::multicast::join_group(multicast_address));

		socket_.async_receive_from(boost::asio::buffer(data_, max_length),
				sender_endpoint_,
				boost::bind(&GNetworking::handle_receive_from, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));

		service = new boost::asio::io_service();
		s = new udp::socket(*service, udp::endpoint(udp::v4(), 0));
		udp::resolver resolver(*service);
		udp::resolver::query query(udp::v4(), "127.0.0.1", "4445");
		iterator = new udp::resolver::iterator(resolver.resolve(query));
	}

	void handle_receive_from(const boost::system::error_code& error,
			size_t bytes_recvd) {
		if (!error) {

			socket_.async_receive_from(boost::asio::buffer(data_, max_length),
					sender_endpoint_,
					boost::bind(&GNetworking::handle_receive_from, this,
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred));

			this->_callback(data_, bytes_recvd); // callback
		}
	}

	void runService() {
		io_service->run();
	}

	bool sendData(const char* request)
	{
		size_t request_length = strlen(request);
		s->send_to(boost::asio::buffer(request, request_length), **iterator);
		return true;
	}

	std::tr1::function<void (const char*, int)> _callback;

public:
	virtual ~GNetworking();

	static GNetworking& instance() {
		static boost::asio::io_service io_service;
		static GNetworking INSTANCE(io_service, boost::asio::ip::address::from_string("0.0.0.0"),
				   boost::asio::ip::address::from_string("230.0.0.1"));
		return INSTANCE;
	}

	void start(std::string app, std::string user, std::string pwd)
	{
		this->appz = app;
		this->usr = user;
		this->pwd = pwd;

		this->send(appz+":"+usr+":login:"+pwd+":password:\0");

		boost::thread mythread(&GNetworking::runService, this);
		mythread.start_thread();
	}

	void quit()
	{
		io_service->stop();
		this->send(appz+":"+usr+":quit:\0");
	}

	bool send(std::string msg)
	{
		return this->sendData(msg.c_str());
	}

	const std::tr1::function<void(const char*, int)>& getCallback() const {
		return _callback;
	}

	void setCallback(
			const std::tr1::function<void(const char*, int)>& callback) {
		_callback = callback;
	}
};

}

#endif
