/**
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */

#ifndef SECAUTHV5_DEFERREDASDU_H
#define SECAUTHV5_DEFERREDASDU_H

#include <opendnp3/app/APDUHeader.h>

#include <openpal/container/DynamicBuffer.h>
#include <openpal/util/Uncopyable.h>

namespace secauthv5
{

class DeferredASDU : private openpal::Uncopyable
{

	public:	

	DeferredASDU(uint32_t maxAPDUSize);

	void Reset();

	bool IsSet() const;	

	void SetASDU(opendnp3::APDUHeader header, openpal::ReadBufferView asdu);

	openpal::ReadBufferView GetFragment() const { return asdu; }

	opendnp3::APDUHeader GetHeader() const { return header; }
	
	template <class Handler>
	bool Process(const Handler& handler);
	
	private:

	DeferredASDU() = delete;

	bool isSet;	
	opendnp3::APDUHeader header;
	openpal::ReadBufferView asdu;
	openpal::DynamicBuffer buffer;
	
};

template <class Handler>
bool DeferredASDU::Process(const Handler& handler)
{
	if (isSet)
	{
		bool processed = handler(asdu, header, asdu.Skip(opendnp3::APDU_REQUEST_HEADER_SIZE));
		isSet = !processed;
		return processed;
	}
	else
	{
		return false;
	}
}

}

#endif
