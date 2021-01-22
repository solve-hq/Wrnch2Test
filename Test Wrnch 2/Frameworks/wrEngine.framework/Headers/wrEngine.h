/*
 Copyright (c) 2020 wrnch Inc.
 All rights reserved
*/

/**
   @file wrEngine.h
   @brief wrnchAI engine 2.0
*/

#ifndef WRENGINE_H
#define WRENGINE_H

#include <stddef.h>
#include <stdint.h>

/* clang-format off */
#define WRNCH_ENGINE_API_MAJOR 2
#define WRNCH_ENGINE_API_MINOR 0
#define WRNCH_ENGINE_API_PATCH 1
/* clang-format on */

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/

    /**
        @brief Describes channel structure of a wrFrame.
    */
    enum wrFrameType
    {
        wrFrameType_BGR8,    /**< 8-bit BGR channel order */
        wrFrameType_RGBA8,   /**< 8-bit BGRA channel order */
        wrFrameType_UNKNOWN, /**< Unknown channel order */
    };

    /**
        @brief Used to set engine stream options when calling
        ::wrEngineConfig_SetIntProperty with ::wrEngineConfigProperty_STREAM_FLAGS as
        second parameter. Options are set bitwise.

        For example, to instruct a wrEngine instance to stream 2d pose data and 3d pose data,
        one may use the following:

        \code
        wrEngineConfig_SetIntProperty(
                                       engineConfigPtr, // pointer to wrEngineConfig instance
                                       wrEngineConfigProperty_STREAM_FLAGS,
                                       wrStream_POSE_2D | wrStream_POSE_3D);
        \endcode
    */
    enum wrStreamFlag
    {
        wrStream_POSE_2D = 0x1, /*< Used to signal that 2d pose data should be streamed. */
        wrStream_POSE_3D = 0x2, /*< Used to signal that 3d pose data should be streamed. */
    };

    /**
       @brief Describes orientation of images.
    */
    enum wrImageOrientation
    {
        wrImageOrientation_AUTOMATIC,   /**< wrEngine determines the image orientation if the
                                          device provides a gravity vector. */
        wrImageOrientation_NORMAL,      /**< The pixel data matches the image's intended display
                                          orientation. */
        wrImageOrientation_ROTATED_180, /**< The pixel data is rotated 180 degrees from the intended
                                          display orientation. */
        wrImageOrientation_ROTATED_90_COUNTERCLOCKWISE, /**< The pixel data is rotated 90 degrees
                                                         counter-clockwise from the intended
                                                         display orientation. */
        wrImageOrientation_ROTATED_90_CLOCKWISE, /**< The pixel data is rotated 90 degrees clockwise
                                                   from the intended display orientation. */
    };

    /**
        @struct wrFrame
        @brief Opaque type representing an image (aka "frame").
    */
    struct wrFrame;

    /**
      @brief Get the data pointer of a wrFrame.

      @param frame The wrFrame to inspect.
      @return Pointer to data held by the frame. This data should be interpreted by the type of the
      frame, queryable through ::wrFrame_GetType.
    */
    uint8_t const* wrFrame_GetData(struct wrFrame const* frame);

    /**
      @brief Get the height of a frame.

      @param frame The wrFrame to inspect.
      @return Height of the frame.
    */
    int64_t wrFrame_GetHeight(struct wrFrame const* frame);

    /**
      @brief Get the width of a frame.

      @param frame The wrFrame to inspect.
      @return Width of the frame.
     */
    int64_t wrFrame_GetWidth(struct wrFrame const* frame);

    /**
      @brief Get the timestamp in microseconds at which a frame was engined.

      For frames sourced from webcams, timestamps represent the time duration since the UNIX Epoch.
      For frames sourced by video files, timestamps represent the time duration from the beginning
      of the video.

      @param frame The wrFrame to inspect.
      @return Timestamp in microseconds of the frame.
    */
    uint64_t wrFrame_GetTimestampMicroseconds(struct wrFrame const* frame);

    /**
       @brief Get the type of a wrFrame.

       @param frame The wrFrame to inspect
       @return a wrFrameType describing the format of the frame.
    */
    enum wrFrameType wrFrame_GetType(struct wrFrame const* frame);

    /**
       @brief Get the image orientation of a frame.

       @param frame The wrFrame to inspect.
       @return The orientation of the image.
    */
    enum wrImageOrientation wrFrame_GetImageOrientation(struct wrFrame const* frame);

    /**
       @brief Return codes used by wrEngine.h
    */
    enum wrEngineCode
    {
        wrEngineCode_OK, /**< Operation completed successfully */
        wrEngineCode_ERR,
        wrEngineCode_BAD_ALLOC,
        wrEngineCode_UNSUPPORTED_ON_PLATFORM,
        wrEngineCode_LICENSE_ERROR_ACTIVATION,
        wrEngineCode_LICENSE_ERROR_ACTIVATION_LIMIT,
        wrEngineCode_LICENSE_ERROR_COUNTRY,
        wrEngineCode_LICENSE_ERROR_DEACTIVATION,
        wrEngineCode_LICENSE_ERROR_FINGERPRINT_CHANGED,
        wrEngineCode_LICENSE_ERROR_FINGERPRINT_INVALID,
        wrEngineCode_LICENSE_ERROR_FLOAT_LIMIT,
        wrEngineCode_LICENSE_ERROR_HOST,
        wrEngineCode_LICENSE_ERROR_INVALID_ACTIVATION,
        wrEngineCode_LICENSE_ERROR_INVALID_KEY,
        wrEngineCode_LICENSE_ERROR_INVALID_OFFLINE,
        wrEngineCode_LICENSE_ERROR_INVALID_TYPE,
        wrEngineCode_LICENSE_ERROR_IO,
        wrEngineCode_LICENSE_ERROR_IP,
        wrEngineCode_LICENSE_ERROR_LEASE,
        wrEngineCode_LICENSE_ERROR_MALFORMED,
        wrEngineCode_LICENSE_ERROR_NOT_FOUND,
        wrEngineCode_LICENSE_ERROR_OS,
        wrEngineCode_LICENSE_ERROR_OTHER,
        wrEngineCode_LICENSE_ERROR_PERMISSIONS,
        wrEngineCode_LICENSE_ERROR_SERVER_ERROR,
        wrEngineCode_LICENSE_ERROR_SERVER_INVALID,
        wrEngineCode_LICENSE_ERROR_SERVER_LICENSE_EXPIRED,
        wrEngineCode_LICENSE_ERROR_SERVER_LICENSE_INVALID,
        wrEngineCode_LICENSE_ERROR_SERVER_LICENSE_SUSPENDED,
        wrEngineCode_LICENSE_ERROR_SYS_TIME,
        wrEngineCode_LICENSE_ERROR_VERSION,
        wrEngineCode_LICENSE_ERROR_VM,
        wrEngineCode_LICENSE_EXPIRED,
        wrEngineCode_LICENSE_GRACE_PERIOD_OVER,
        wrEngineCode_LICENSE_PATH_ERROR,
        wrEngineCode_LICENSE_REVOKED,
        wrEngineCode_LICENSE_SUSPENDED,
        wrEngineCode_TPOSE_CALIBRATION_DONE, /**< T pose calibration completed successfully */
        wrEngineCode_TPOSE_CALIBRATION_JOINTS_MISSING,
        wrEngineCode_TPOSE_CALIBRATION_NO_PERSON_DETECTED,
        wrEngineCode_TPOSE_CALIBRATION_PERSON_MOVING,
        wrEngineCode_TPOSE_CALIBRATION_PERSON_NOT_FACING_CAMERA,
        wrEngineCode_TPOSE_CALIBRATION_PROGRESSING_OK,
        wrEngineCode_UNKNOWN_ERROR,
    };

    /**
       @brief Give a human-readable description of a wrEngineCode.

       @param code The wrEngineCode to describe.
       @return A human-readable description of the code. The returned pointer is not null and points
       to a valid C-string (i.e. is null-byte-terminated) with static storage duration.
    */
    char const* wrEngineCode_Describe(enum wrEngineCode code);

    /**
       @struct wrCameraDeviceInfo
       @brief Opaque type to describe camera properties.
    */
    struct wrCameraDeviceInfo;

    /**
       @brief Describes camera position.
    */
    enum wrCameraDevicePosition
    {
        wrCameraDevicePosition_FRONT,   /**< Refers to front-facing cameras on mobile devices. */
        wrCameraDevicePosition_BACK,    /**< Refers to back-facing cameras on mobile devices. */
        wrCameraDevicePosition_UNKNOWN, /**< Refers to an undescribable camera position (e.g.
                                           desktop webcams) */
    };

    /**
       @brief Create a wrCameraDeviceInfo.

       @return On success, returns a non-null pointer to a wrCameraDeviceInfo. Users should call
       ::wrCameraDeviceInfo_Destroy when finished to free any resources associated to the camera
       device info. On failure (which should only be in out-of-memory situations), returns `NULL`.
    */
    struct wrCameraDeviceInfo* wrCameraDeviceInfo_Create(void);

    /**
       @brief Destroy a wrCameraDeviceInfo.

       Note it is safe to call ::wrCameraDeviceInfo_Destroy on `NULL`. Note also that passing a
       pointer to a destroyed wrCameraDeviceInfo to any wrEngine.h function results in undefined
       behaviour.

       @param info Pointer to the wrCameraDeviceInfo to destroy.
       @see wrCameraDeviceInfo_Create
     */
    void wrCameraDeviceInfo_Destroy(struct wrCameraDeviceInfo* info);

    /**
       @brief Get the id of a camera held in a wrCameraDeviceInfo.

       @param info Pointer to wrCameraDeviceInfo to query.
       @return C-string of the id. The string is owned by info.
    */
    const char* wrCameraDeviceInfo_GetId(struct wrCameraDeviceInfo const* info);

    /**
       @brief Get the friendly name of a camera held in a wrCameraDeviceInfo.

       @param info Pointer to wrCameraDeviceInfo to query.
       @return C-string of the friendly name. The string is owned by info.
    */
    const char* wrCameraDeviceInfo_GetFriendlyName(struct wrCameraDeviceInfo const* info);

    /**
       @brief Get the device position of a camera held in a wrCameraDeviceInfo.

       @param info Pointer to wrCameraDeviceInfo to query.
    */
    enum wrCameraDevicePosition wrCameraDeviceInfo_GetPosition(
        struct wrCameraDeviceInfo const* info);

    /**
       @brief Get the number of cameras.
    */
    uint32_t wrEngine_GetNumCameraDevices(void);

    /**
       @brief Get the camera device info of a camera.

       @param deviceInfoOut Pointer to valid wrCameraDeviceInfo (created by
       ::wrCameraDeviceInfo_Create). If `index < wrEngine_GetNumCameraDevices()`, the requested
       device info is written to deviceInfoOut.
       @param index Index of the requsted device to query.
       @return ::wrEngineCode_OK on success (i.e. `index < wrEngine_GetNumCameraDevices()`), else
       a nonzero error.
       @see wrEngine_GetNumCameraDevices
       @see wrCameraDeviceInfo_Create
    */
    enum wrEngineCode wrEngine_GetCameraDeviceInfo(struct wrCameraDeviceInfo* deviceInfoOut,
                                                   uint32_t index);

    /**
      @brief Integer properties to set on a wrEngineConfig instance using
      ::wrEngineConfig_SetIntProperty.
    */
    enum wrEngineConfigPropertyInt
    {
        wrEngineConfigProperty_STREAM_FLAGS,      /**< Specify which data to stream. Default is
                                                     wrStream_POSE_3D */
        wrEngineConfigProperty_TCP_LISTEN_PORT,   /**< Port number wrEngine listens on for streaming
                                                     data. Default is 6888 */
        wrEngineConfigProperty_IMAGE_ORIENTATION, /**< Set this property to override the automatic
                                                     rotation adjustment. Default value on a
                                                     wrEngineConfig is
                                                     ::wrImageOrientation_AUTOMATIC. */
    };

    /**
       @brief String properties to set on a wrEngineConfig instance using
       ::wrEngineConfig_SetStringProperty.
    */
    enum wrEngineConfigPropertyString
    {
        wrEngineConfigProperty_DATA_SERVICE_NAME, /**< Name of the discoverable service for
                                                      streaming data. If not set on a wrEngine
                                                      instance, a default name of "wrnch-pose" is
                                                      used. */
        wrEngineConfigProperty_LICENSE_STRING,    /**< wrnch license string. */
    };

    /**
       @brief Integer properties to set on a wrCameraConfig instance when using
       ::wrCameraConfig_SetIntProperty.
    */
    enum wrCameraConfigPropertyInt
    {
        wrCameraConfigProperty_WIDTH,
        wrCameraConfigProperty_HEIGHT,
    };

    /**
       @brief Float properties to set on a wrCameraConfig instance when using
       ::wrCameraConfig_SetFloatProperty
    */
    enum wrCameraConfigPropertyFloat
    {
        wrCameraConfigProperty_FPS, /**< Desired frames per second. */
    };

    /**
       @brief Float array properties to set on a wrCameraConfig instance when using
       ::wrCameraConfig_SetFloatArrayProperty
    */
    enum wrCameraConfigPropertyFloatArray
    {
        wrCameraConfigProperty_CAMERA_MATRIX, /**< 3x3 matrix of camera intrinsics specified in
                                                 row-major order. When passed as an argument to
                                                 ::wrCameraConfig_SetFloatArrayProperty, the value
                                                 argument must point to a valid region of at least
                                                 3x3 = 9 floats. */
        wrCameraConfigProperty_GROUND_PLANE,  /**< 4x4 matrix of ground plane to camera transform
                                                 specified in row-major order. When passed as an
                                                 argument to ::wrCameraConfig_SetFloatArrayProperty,
                                                 the value argument must point to a valid region of
                                                 at least 4x4 = 16 floats. */
    };

    /**
       @brief String properties to set on a wrCameraConfig instance when using
       ::wrCameraConfig_SetStringProperty.
    */
    enum wrCameraConfigPropertyString
    {
        /* Device name of the camera to open, as obtained
           with wrEngine_GetCameraDeviceInfo() + wrCameraDeviceInfo_GetId().
           If not specified, the first camera that comes up in a device
           enumeration will be used by default.
        */
        wrCameraConfigProperty_DEVICE_ID,
    };

    /**
       @brief Callback type used by a wrEngine instance to report detections to in-memory clients.

       @param frame The image (aka "frame") on which detections were computed.
       @param serializedDetections Pointer to serialized wrXchng data describing detections.
       @param serializedDetectionsLen Length of the serializedDetections array.
       @param userData Type-erased pointer to client data to be passed to the callback.
       @see wrEngineConfig_SetDetectionCallback
       @see wrEngine
    */
    typedef void (*wrDetectionCallback)(struct wrFrame const* frame,
                                        char const* serializedDetections,
                                        size_t serializedDetectionsLen,
                                        void* userData);

    /**
      @brief Callback type used to communicate end-of-processing for video files.

      @param userData Type-erased pointer to user data to be passed to the callback when called.
      @see wrEngine_OpenVideoFile
    */
    typedef void (*wrVideoDoneCallback)(void* userData);

    /**
       @brief Callback type used to communicate progress updates of T-Pose calibration.

       @param result Indicates status of the T-pose calibration:
       ::wrEngineCode_TPOSE_CALIBRATION_DONE indicates successful completion, anything else
       indicates that the process is in progress, or that there are problems.
       @param userData Type-erased pointer to client data to be passed to the callback.
    */
    typedef void (*wrTPoseCallback)(enum wrEngineCode result, void* userData);

    /**
        @struct wrEngineConfig
        @brief Opaque type to configure creation of a wrEngine instance.
    */
    struct wrEngineConfig;

    /**
       @brief Create a wrEngineConfig instance.

       @return On success, returns a non-null pointer to a wrEngineConfig. Users should call
       ::wrEngineConfig_Destroy when finished to free any resources associated to the engine
       config. On failure (which should only be in out-of-memory situations), returns `NULL`.
    */
    struct wrEngineConfig* wrEngineConfig_Create(void);

    /**
       @brief Destroy a wrEngineConfig instance.

       Note it is safe to call ::wrEngineConfig_Destroy on `NULL`. Note also that passing a pointer
       to a destroyed wrEngineConfig to any wrEngine.h function results in undefined behaviour.

       @param config Pointer to the wrEngineConfig to destroy.
       @see wrEngineConfig_Create
    */
    void wrEngineConfig_Destroy(struct wrEngineConfig* config);

    /**
       @brief Set a detection callback on a wrEngineConfig instance.

       After calling ::wrEngineConfig_SetDetectionCallback and subsequently ::wrEngine_Create
       using the same wrEngineConfig, a detection callback has been set on the resulting wrEngine
       instance.

       @param config Pointer to wrEngineConfig on which to store the callback.
       @param callback ::wrDetectionCallback to set on the ::wrEngineConfig. Passing `NULL` is
       allowed. Note that `callback` is called asynchronously so it is up to clients to ensure their
       code (including the callback definition) is free of data races and race conditions.
       @param userData Type-erased pointer to client data to be passed to the callback.
    */
    void wrEngineConfig_SetDetectionCallback(struct wrEngineConfig* config,
                                             wrDetectionCallback callback,
                                             void* userData);

    /**
        @deprecated
        @brief Set the endpoint to stream UDP data.

        @param config The wrEngineConfig on which to set the UDP streaming endpoint.
        @param address Address string. Must point to a valid and null-terminated char
        sequence else the behaviour is undefined.
        @param port Port number to connect to.
    */
    void wrEngineConfig_SetStreamingEndpoint(struct wrEngineConfig* config,
                                             const char* address,
                                             int port);

    /**
       @brief Set an integer property on a wrEngineConfig.

       @param config Pointer to the wrEngineConfig on which to set a property.
       @param property Enumerator describing property name.
       @param value The value of the property to set.
       @return ::wrEngineCode_OK if the property is one of the named enumerators of
       ::wrEngineConfigPropertyInt, else a nonzero error.
    */
    enum wrEngineCode wrEngineConfig_SetIntProperty(struct wrEngineConfig* config,
                                                    enum wrEngineConfigPropertyInt property,
                                                    int value);

    /**
       @brief Set a string property on a wrEngineConfig.

       Note that the string is deep-copied into the wrEngineConfig (it is not copied by pointer).

       @param config Pointer to the wrEngineConfig on which to set a property.
       @param property Enumerator describing property name.
       @param value The value of the property to set. Must point to a valid and null-terminated char
       sequence else the behaviour is undefined.
       @return ::wrEngineCode_OK if the property is one of the named enumerators of
       ::wrEngineConfigPropertyString, else a nonzero error.
    */
    enum wrEngineCode wrEngineConfig_SetStringProperty(struct wrEngineConfig* config,
                                                       enum wrEngineConfigPropertyString property,
                                                       const char* value);

    /**
        @struct wrEngine

        @brief Opaque type pointing to a wrnchAI engine.

        wrEngine instances are responsible for capturing frames from a webcam or video
        source, detecting humans in those frames, and reporting detections through either a
        socket interface or through in-memory callbacks.

        When configured by a call to ::wrEngineConfig_SetDetectionCallback with a callback `cb`
        and user data `userData`, as detections become available on a frame `f`,
        the engine asynchronously calls

        \code
        cb(f, serializedWrXchng, serializedWrXchngLength, userData)
        \endcode

        to communicate the frame and the detected humans in the frame (in
        serialized wrnch Xchng format). This is repeated for all frames processed by the wrEngine.

       wrEngine instances can also broadcast detections over the network either with UDP streaming
       (throgh ::wrEngineConfig_SetStreamingEndpoint), or with TCP (see
       ::wrEngineConfigProperty_TCP_LISTEN_PORT).

       Errors are reported asynchronously and require quering with ::wrEngine_GetError.

       Note on thread safety: given that a wrEngine instance processes frames asyncronously,
       all wrEngine.h functions which accept at `wrEngine*` are thread safe unless indicated
       otherwise.
   */
    struct wrEngine;

    /**
       @brief Create a wrEngine instance.

       On success, creates a wrEngine instance. Note the wrEngine created does not start grabbing
       frames immediately. This requires calling ::wrEngine_OpenVideoFile or
       ::wrEngine_OpenCamera. Note also this function can take some time to complete.

       Example usage:

       \code
       struct wrEngineConfig* engineConfig = wrEngineConfig_Create();
       if (engineConfig == `NULL`)
       {
          // error condition, handle appropriately (e.g. exiting your app)
       }

       // ... set some properties on wrEngineConfig

       struct wrEngine* engine = `NULL`; // not strictly necessary to initialize.
       enum wrEngineCode code = wrEngine_Create(&engine, config);

       if (code != wrEngineCode_OK)
       {
         // error condition, handle appropriately (e.g. exiting your app)
       }
       else {
         // engine now points to a valid wrEngine instance
       }
       \endcode

       @param enginePtrPtr Pointer to pointer to wrEngine instance. On success, `*enginePtr` is
       not `NULL`, and `*enginePtrPtr` points to a valid wrEngine instance. On failure,
       `*enginePtr` is set to `NULL`. Note that this parameter must point to a valid ::wrEngine*
       pointer, otherwise the behaviour is undefined.
       @param config The wrEngineConfig describing the configuration of the desired wrEngine to
       create.
       @return ::wrEngineCode_OK on success, else a nonzero error.
    */
    enum wrEngineCode wrEngine_Create(struct wrEngine** enginePtrPtr,
                                      struct wrEngineConfig const* config);


    /**
       @struct wrCameraConfig
       @brief Configuration struct describing a camera.
    */
    struct wrCameraConfig;

    /**
       @brief Create a wrCameraConfig instance.

       @return On success, returns a non-null pointer to a wrCameraConfig. Users should call
       ::wrCameraConfig_Destroy when finished to free any resources assocated to the camera config.
       On failure (which should only be in out-of-memory situations), returns `NULL`.
    */
    struct wrCameraConfig* wrCameraConfig_Create(void);

    /**
       @brief Destroy a wrCameraConfig instance.

       Note it is safe to call ::wrCameraConfig_Destroy on `NULL`. Note also that passing a pointer
       to a destroyed wrCameraConfig to any wrEngine.h function results in undefined behaviour.

       @param config Pointer to the wrCameraConfig to destroy.
       @see wrCameraConfig_Create
     */
    void wrCameraConfig_Destroy(struct wrCameraConfig* config);

    /**
       @brief Set an integer property on a wrCameraConfig

       @param config Pointer to the wrEngineConfig on which to set a property.
       @param property Enumerator describing property name.
       @param value The value of the property to set.
       @return ::wrEngineCode_OK if the property is one of the named enumerators of
       ::wrEngineConfigPropertyInt, else a nonzero error.
    */
    enum wrEngineCode wrCameraConfig_SetIntProperty(struct wrCameraConfig* config,
                                                    enum wrCameraConfigPropertyInt property,
                                                    int value);

    /**
       @brief Set an float property on a wrCameraConfig

       @param config Pointer to the wrCameraConfig on which to set a property.
       @param property Enumerator describing property name.
       @param value The value of the property to set.
       @return ::wrEngineCode_OK if the property is one of the named enumerators of
       ::wrCameraConfigPropertyFloat, else a nonzero error.
    */
    enum wrEngineCode wrCameraConfig_SetFloatProperty(struct wrCameraConfig* config,
                                                      enum wrCameraConfigPropertyFloat property,
                                                      float value);

    /**
       @brief Set an float array property on a wrCameraConfig

       Note that the float array is deep-copied into the config object (it is not copied by
       pointer).

       @param config Pointer to the wrCameraConfig on which to set a property.
       @param property Enumerator describing property name.
       @param value Pointer to the float array to be copied into the engine config. Note that the
       length of this array must be at least as long as the required length specified by the
       property enumerator argument, else the behaviour is undefined. For example, when passing
       ::wrCameraConfigProperty_CAMERA_MATRIX, value must point to a valid region of at least 9
       floats.
       @return ::wrEngineCode_OK if the property is one of the named enumerators of
       ::wrCameraConfigPropertyFloat, else a nonzero error.
    */
    enum wrEngineCode wrCameraConfig_SetFloatArrayProperty(
        struct wrCameraConfig* config,
        enum wrCameraConfigPropertyFloatArray property,
        const float* value);

    /**
       @brief Set a string property on a wrCameraConfig.

       Note that the string is deep-copied into the wrCameraConfig (it is not copied by pointer).

       @param config Pointer to the wrCameraConfig on which to set a property.
       @param property Enumerator describing property name.
       @param value The value of the property to set. Must point to a valid and null-terminated char
       sequence else the behaviour is undefined.
       @return ::wrEngineCode_OK if the property is one of the named enumerators of
       ::wrCameraConfigPropertyString, else a nonzero error.
    */
    enum wrEngineCode wrCameraConfig_SetStringProperty(struct wrCameraConfig* config,
                                                       enum wrCameraConfigPropertyString property,
                                                       const char* value);

    /**
       @brief Instruct a wrEngine instance to open a camera device and start grabbing and
       processing frames.

       If a camera is already open in the wrEngine,
       it will be closed first. You will also need to call ::wrEngine_StartTPoseCalibration
       when camera parameters change.

       @param wrengine Pointer to wrEngine instance which should open the desired camera.
       @param config Pointer to camera configuration describing the camera to open.
       @return ::wrEngineCode_OK on success, else a nonzero error code. Note that in error cases,
       a log is written to standard error describing the error encountered.
    */
    enum wrEngineCode wrEngine_OpenCamera(struct wrEngine* wrengine,
                                          struct wrCameraConfig const* config);

    /**
       @brief Closes and release resources associated with the camera
       @param wrengine The wrengine instance which should close its camera (if it has one open).
    */
    void wrEngine_CloseCamera(struct wrEngine* wrengine);

    /**
        @brief Instruct a wrEngine instance to open a video file and start grabbing and processing
        frames.

        If a camera or video is already open, it will be closed first.

        @param wrengine Pointer to wrEngine instance to open the video on.
        @param videoPath The on-disk path to the video file to open.
        @param callback wrVideoDoneCallback instance to be called when wrengine has finished
        processing all frames. Note this is called asynchronously on a thread, so users should be
        careful to avoid data races and race conditions in their code (including in the callback
        definition).
        @param userData Type-erased pointer to user data to be passed to callback when wrengine is
        finished processing frames.
        @param cameraMatrix Pointer to camera intrisics array. cameraMatrix must point to a valid
        region of memory containing at least 3x3=9 floats, else the behaviour is undefined.
        @param groundPlane Pointer to ground plane to camera transform. groundPlane must point to a
        valid region of memory containing at least 4x4=16 floats, else the behaviour is undefined.
     */
    enum wrEngineCode wrEngine_OpenVideoFile(struct wrEngine* wrengine,
                                             const char* videoPath,
                                             wrVideoDoneCallback callback,
                                             void* userData,
                                             const float* cameraMatrix,
                                             const float* groundPlane);

    /**
       @brief Stop and destroy a wrEngine instance.

       All asynchronous tasks are signaled to stop. Blocks until async tasks actually complete.
       Cleans up all resources owned by the wrEngine instance. Note that passing a pointer to a
       destroyed wrEngine instance to any wrEngine.h function results in undefined behaviour. It
       is safe to call wrEngine_Destroy on `NULL`.

       @param wrengine Pointer to wrEngine instance to shut down and destroy.
    */
    void wrEngine_Destroy(struct wrEngine* wrengine);

/** Maximum needed buffer size for error messages */
#define wrEngine_MAX_ERR_LEN 256

    /**
      @brief Query a wrEngine instance for any error that may be set on it.

      @param wrengine The wrEngine to query.
      @param outError pointer to a char array of at least ::wrEngine_MAX_ERR_LEN valid bytes. If
      the engine holds an error, at most `::wrEngine_MAX_ERR_LEN - 1` bytes are written to
      `outError`, leaving space for one null byte (which it writes). If `wrengine` holds an error
      and `outError` does not point to a valid char array of at least ::wrEngine_MAX_ERR_LEN bytes,
      then the behaviour is undefined. If wrengine holds no error, then nothing is written to
      `outError`.
      @return 1 if the engine holds an error, 0 if it does not.
    */
    uint8_t wrEngine_GetError(struct wrEngine const* wrengine, char* outError);

    /**
       @brief Get the length of the serialized wrXchng FrameMetadata.

       @param wrengine The engine to query.
    */
    size_t wrEngine_GetMetadataLen(struct wrEngine const* wrengine);

    /**
       @brief Get a pointer to serialized wrXchng FrameMetadata.

       The length of the serialized message is given by ::wrEngine_GetMetadataLen.

       @param wrengine The wrEngine to query.
       @param outData Pointer to char array to copy the serialized metadata to.
       @param outDataLen Byte count of valid bytes in `outData`.
       @return outData if outDataLen is greater than or equal to the true serialized metadata
       length, or `NULL` otherwise.
    */
    const char* wrEngine_GetMetadata(struct wrEngine const* wrengine,
                                     char* const outData,
                                     size_t outDataLen);

    /**
       @brief Start T-pose calibration on a wrEngine.

       T-pose calibration collects a sequence of frames until it is confident it has a decent T-pose
       estimate. If callback was non-null, it is called on userData routinely with a status code
       to describe the state of the calibration procedure and to alert the user of any issues with
       the process.

       @param wrengine wrEngine instance on which to start T-pose calibration.
       @param callback wrTPoseCallback called at T-pose completion time with userData. Passing
       `NULL` is allowed. Note that `callback` is called asynchronously so it is up to clients to
       ensure their code (including the callback definition) is free of data races and race
       conditions.
       @param userData Type-erased pointer to client data to be passed to the callback
       @return ::wrEngineCode_OK on success, else a nonzero error value.
    */
    enum wrEngineCode wrEngine_StartTPoseCalibration(struct wrEngine* wrengine,
                                                     wrTPoseCallback callback,
                                                     void* userData);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*WRENGINE_H*/
