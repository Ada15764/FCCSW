################################################################################
# Package: DataObjects
################################################################################
gaudi_subdir(DataObjects v1r0)

# this declaration will not be needed in the future
gaudi_depends_on_subdirs(GaudiAlg)

find_package(HepMC)
find_package(FastJet)
find_package(PODIO)

gaudi_add_dictionary(DataObjects dict/dictionary.h  dict/dictionary.xml
                     INCLUDE_DIRS DataObjects PODIO
                     LINK_LIBRARIES DataObjects PODIO)

gaudi_add_library(DataObjects
		  src/*.cc
                  INCLUDE_DIRS HepMC FastJet
                  LINK_LIBRARIES HepMC GaudiAlgLib FastJet
		  PUBLIC_HEADERS DataObjects)
