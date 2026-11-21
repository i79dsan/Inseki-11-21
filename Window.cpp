#include "Window.h"

void Window::Init(Vector2 size) {
	size_ = size;
}

Vector2 Window::GetSize() const {
	return size_;
}

int Window::GetColorBitDepth() const {
	return colorBitDepth_;
}