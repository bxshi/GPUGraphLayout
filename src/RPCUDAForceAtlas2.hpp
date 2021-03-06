/*
 ==============================================================================

 RPCUDAForceAtlas2.hpp
 Copyright (C) 2016, 2017  G. Brinkmann

 This file is part of graph_viewer.

 graph_viewer is free software: you can redistribute it and/or modify
 it under the terms of version 3 of the GNU Affero General Public License as
 published by the Free Software Foundation.

 graph_viewer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with graph_viewer.  If not, see <https://www.gnu.org/licenses/>.

 ==============================================================================
*/

#ifndef RPCUDAForceAtlas2_hpp
#define RPCUDAForceAtlas2_hpp
#include "RPForceAtlas2.hpp"

namespace RPGraph
{
    class CUDAForceAtlas2: public ForceAtlas2
    {
    public:
        CUDAForceAtlas2(GraphLayout &layout);
        ~CUDAForceAtlas2();
        void benchmark() override;
        void doStep() override;
        void sync_layout() override;

    private:
        /// CUDA Specific stuff.
        // Host storage.
        float *mass, *posx, *posy;
        float *fx, *fy, *fx_prev, *fy_prev;

        // Quick way to represent a graph on the GPU
        int *sources, *targets;

        // Pointers to device memory (all suffixed with 'l').
        int   *errl,  *sortl, *childl, *countl, *startl;
        int   *sourcesl, *targetsl;
        float *massl, *posxl, *posyl;
        float *minxl, *minyl, *maxxl, *maxyl;
        float *fxl, *fyl, *fx_prevl, *fy_prevl;
        float *swgl, *etral;

        int mp_count; // Number of multiprocessors on GPU.
        int max_threads_per_block;
        int nnodes;
        int nbodies;
        int nedges;

        void sendGraphToGPU();
        void sendLayoutToGPU();
        void retrieveLayoutFromGPU();
        void freeGPUMemory();
    };
};


#endif /* RPCUDAForceAtlas2_hpp */
