//
// Created by Jack Armstrong on 3/23/19.
//

#include "input.h"

bool is_key_down(int k){
    return (bool)glfwGetKey(window,k);
}
