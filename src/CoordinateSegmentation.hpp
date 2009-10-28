/*  cbr
 *  CoordinateSegmentation.hpp
 *
 *  Copyright (c) 2009, Ewen Cheslack-Postava
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
 *  * Neither the name of cbr nor the names of its contributors may
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

#ifndef _CBR_COORDINATE_SEGMENTATION_HPP_
#define _CBR_COORDINATE_SEGMENTATION_HPP_

#include "Utility.hpp"
#include "SpaceContext.hpp"
#include "LoadMonitor.hpp"

namespace CBR {

typedef std::vector<BoundingBox3f> BoundingBoxList;

/** Handles the segmentation of the space into regions handled by servers.
 *  Answers queries of the type
 *   position -> ServerID
 *   ServerID -> region
 */
class CoordinateSegmentation : public MessageRecipient {
public:
    /** Listens for updates about the coordinate segmentation. */
    class Listener {
    public:
        virtual ~Listener() {}

        struct SegmentationInfo {
            ServerID server;
            BoundingBoxList region;
        };
        virtual void updatedSegmentation(CoordinateSegmentation* cseg, const std::vector<SegmentationInfo>& new_segmentation) = 0;
    }; // class Listener

    CoordinateSegmentation(SpaceContext* ctx);
    virtual ~CoordinateSegmentation() {}

    virtual ServerID lookup(const Vector3f& pos) = 0;
    virtual BoundingBoxList serverRegion(const ServerID& server)  = 0;
    virtual BoundingBox3f region()  = 0;
    virtual uint32 numServers()  = 0;

    void addListener(Listener* listener);
    void removeListener(Listener* listener);

    // Callback from MessageDispatcher
    virtual void receiveMessage(Message* msg) = 0;

    virtual void service() = 0;

    virtual void migrationHint( std::vector<ServerLoadInfo>& svrLoadInfo ) {  }

protected:
    void notifyListeners(const std::vector<Listener::SegmentationInfo>& new_segmentation);

    SpaceContext* mContext;
    TimeProfiler::Stage* mServiceStage;
private:
    CoordinateSegmentation();

    std::set<Listener*> mListeners;
}; // class CoordinateSegmentation

} // namespace CBR

#endif
