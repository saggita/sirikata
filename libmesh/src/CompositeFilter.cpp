/*  Sirikata
 *  CompositeFilter.cpp
 *
 *  Copyright (c) 2011, Ewen Cheslack-Postava
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of Sirikata nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sirikata/mesh/CompositeFilter.hpp>

namespace Sirikata {
namespace Mesh {

CompositeFilter::Exception::Exception(const String& msg)
 : std::exception(), _msg(msg)
{
}

CompositeFilter::Exception::~Exception() throw() {
}

const char* CompositeFilter::Exception::what() const throw() {
    return _msg.c_str();
}

CompositeFilter::CompositeFilter() {

}

CompositeFilter::CompositeFilter(const std::vector<String>& names_and_args) {
    assert(names_and_args.size() % 2 == 0);
    for(uint32 i = 0; i < names_and_args.size(); i+=2)
        add(names_and_args[i], names_and_args[i+1]);
}

void CompositeFilter::add(const String& name, const String& args) {
    if (!FilterFactory::getSingleton().hasConstructor(name))
        throw CompositeFilter::Exception("No filter named " + name);
    FilterPtr next_filter(
        FilterFactory::getSingleton().getConstructor(name)(args)
    );
    mFilters.push_back(next_filter);
}

FilterDataPtr CompositeFilter::apply(FilterDataPtr input) {
    FilterDataPtr result = input;
    for(uint32 i = 0; i < mFilters.size(); i++) {
        result = mFilters[i]->apply(result);
    }
    return result;
}

} // namespace Mesh
} // namespace Sirikata
