/**
 * File generated by Jenny -- https://github.com/LanderlYoung/Jenny
 *
 * For bug report, please refer to github issue tracker https://github.com/LanderlYoung/Jenny/issues,
 * or contact author landerlyoung@gmail.com.
 */
#include <NativeDrawableProxy.h>
#include "NativeDrawable.h"
#include "gen/android_DrawableProxy.h"
#include "gen/android_RectProxy.h"
#include "gen/android_PaintProxy.h"
#include "gen/android_CanvasProxy.h"
#include "gen/android_StyleProxy.h"


class State {
private:
    uint _color;
public:
    jobject const paint;

    State(jobject paint) : _color(0xFF), paint(paint) {}

    int color() {
        return _color | 0xFF000000;
    }

    void change() {
        _color *= 97;
        if (_color == 0) {
            _color = 0xFF;
        }
    }
};


/*
 * Class:     io_github_landerlyoung_jennysampleapp_NativeDrawable
 * Method:    private final long nativeInit()
 * Signature: ()J
 */
jlong NativeDrawable::nativeInit(JNIEnv *env, jobject thiz) {
    using android::PaintProxy;

    android::StyleProxy fillType(env, android::StyleProxy::getFILL(env));
    auto paint = PaintProxy::newInstance(env, PaintProxy::ANTI_ALIAS_FLAG);
    paint.setStyle(*fillType);

    auto paintGlobal = env->NewGlobalRef(*paint);
    fillType.deleteLocalRef();
    paint.deleteLocalRef();

    return reinterpret_cast<jlong>(new State(paintGlobal));
}

/*
 * Class:     io_github_landerlyoung_jennysampleapp_NativeDrawable
 * Method:    public final void onClick()
 * Signature: ()V
 */
void NativeDrawable::onClick(JNIEnv *env, jobject thiz) {
    State *state = reinterpret_cast<State *>(NativeDrawableProxy(env, thiz).getNativeHandle());
    state->change();
}

/*
 * Class:     io_github_landerlyoung_jennysampleapp_NativeDrawable
 * Method:    public void draw(android.graphics.Canvas canvas)
 * Signature: (Landroid/graphics/Canvas;)V
 */
void NativeDrawable::draw(JNIEnv *env, jobject thiz, jobject _canvas) {
    using namespace android;
    State *state = reinterpret_cast<State *>(NativeDrawableProxy(env, thiz).getNativeHandle());
    DrawableProxy drawable(env, thiz);
    RectProxy bounds(env, drawable.getBounds());
    PaintProxy paint(env, state->paint);
    CanvasProxy canvas(env, _canvas);

    paint.setColor(state->color());
    canvas.drawCircle(
            bounds.exactCenterX(),
            bounds.exactCenterY(),
            std::min(bounds.exactCenterX(), bounds.exactCenterY()) * 0.7f,
            *paint);

    bounds.deleteLocalRef();
}

/*
 * Class:     io_github_landerlyoung_jennysampleapp_NativeDrawable
 * Method:    public final void release()
 * Signature: ()V
 */
void NativeDrawable::release(JNIEnv *env, jobject thiz) {
    State *state = reinterpret_cast<State *>(NativeDrawableProxy(env, thiz).getNativeHandle());
    env->DeleteGlobalRef(state->paint);
    delete state;
}



