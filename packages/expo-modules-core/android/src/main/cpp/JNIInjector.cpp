// Copyright © 2021-present 650 Industries, Inc. (aka Expo)

#include "JSIInteropModuleRegistry.h"
#include "JavaScriptModuleObject.h"
#include "JavaScriptValue.h"
#include "JavaScriptObject.h"
#include "JavaScriptTypedArray.h"
#include "CachedReferencesRegistry.h"

#if IS_NEW_ARCHITECTURE_ENABLED
#include "FabricComponentsRegistry.h"
#endif

#include <jni.h>
#include <fbjni/fbjni.h>

// Install all jni bindings
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
  return facebook::jni::initialize(vm, [] {
    // Loads references to often use Java classes
    expo::CachedReferencesRegistry::instance()->loadJClasses(jni::Environment::current());

    expo::JSIInteropModuleRegistry::registerNatives();
    expo::JavaScriptModuleObject::registerNatives();
    expo::JavaScriptValue::registerNatives();
    expo::JavaScriptObject::registerNatives();
    expo::JavaScriptTypedArray::registerNatives();
#if IS_NEW_ARCHITECTURE_ENABLED
    expo::FabricComponentsRegistry::registerNatives();
#endif
  });
}
