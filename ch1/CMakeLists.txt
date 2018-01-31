ADD_EXECUTABLE(daytimetcpsrv daytimetcpsrv.c)
TARGET_LINK_LIBRARIES(daytimetcpsrv unp)

ADD_EXECUTABLE(daytimetcpcli daytimetcpcli.c)
TARGET_LINK_LIBRARIES(daytimetcpcli unp)
