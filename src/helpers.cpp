#include "helpers.h"

namespace Helpers {
int render_layer_index(RenderLayer rl){
    return static_cast<int>(rl);
}

int render_layer_size()
{
    return static_cast<int>(RenderLayer::MAX_LAYERS);
}

}
