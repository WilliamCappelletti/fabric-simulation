TEMPLATE = lib

CONFIG = staticlib c++11

SOURCES = Systeme.cc Tissu.cc Masse.cc Ressort.cc Vecteur3D.cc Integrateur.cc Int_Euler.cc Int_New.cc Int_Runge.cc Contraintes.cc

HEADERS += \
    Systeme.h Tissu.h Masse.h Vecteur3D.h Integrateur.h Int_Euler.h Int_New.h Int_Runge.h Contraintes.h\
    Dessinable.h \
    SupportADessin.h
