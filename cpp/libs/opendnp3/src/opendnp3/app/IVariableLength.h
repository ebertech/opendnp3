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
#ifndef OPENDNP3_IVARIABLELENGTH_H
#define OPENDNP3_IVARIABLELENGTH_H

#include <openpal/container/WriteBufferView.h>

namespace opendnp3
{

class IVariableLength
{	

public:

	virtual ~IVariableLength() {}

	// The size of the object in its current configuration
	virtual uint32_t Size() const = 0;

	// attempt to write the object to the destination buffer
	virtual bool Write(openpal::WriteBufferView& dest) const = 0;

	// attempt to read the object from the input buffer
	virtual bool Read(const openpal::ReadBufferView& input) = 0;

protected:

	static bool ReadUInt16PrefixedField(openpal::ReadBufferView& input, openpal::ReadBufferView& dest);

};

}

#endif