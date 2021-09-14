#ifndef IWINDOWOPENER_H
#define IWINDOWOPENER_H
class IWindowOpener{
public:
    virtual void OpenMainWindow()=0;
    virtual void OpenLoginWindow()=0;
    virtual void OpenSignupindow()=0;
};
#endif // IWINDOWOPENER_H
