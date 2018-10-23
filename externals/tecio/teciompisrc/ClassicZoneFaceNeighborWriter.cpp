#include "ClassicZoneFaceNeighborWriter.h"
#include "FaceNeighborGeneratorAbstract.h"
#include "FileWriterInterface.h"
#include "fileStuff.h"
#include "SzlFileLoader.h"
#include "writeValueArray.h"
namespace tecplot { namespace ___3933 { namespace { char const* USER_FACE_NEIGHBOR_COUNT_LABEL = "userFaceNeighborCount"; char const* USER_FACE_NEIGHBOR_MARKER_LABEL = "userFaceNeighborMarker*"; char const* USER_FACE_NEIGHBORS_LABEL = "UserFaceNeighbors"; } ClassicZoneFaceNeighborWriter::ClassicZoneFaceNeighborWriter( FaceNeighborGeneratorAbstract& faceNeighborGenerator, ___4636 zone, ___4636 ___341) : m_faceNeighborGenerator(faceNeighborGenerator) , ___2677(zone) , m_baseZone(___341) , m_zoneNumberLabel(SZPLT_ZONE_NUM_DESCRIPTION) {} ___372 ClassicZoneFaceNeighborWriter::write( FileWriterInterface& szpltFile) { REQUIRE(szpltFile.___2041()); ___372 ___2039 = ___4226; if (m_userFaceNeighbors.empty()) m_faceNeighborGenerator.gatherUserFaceNeighbors(m_userFaceNeighbors, ___2677); if (szpltFile.___2002()) { ___2039 = writeValue<uint32_t, false, 0>(szpltFile, USER_FACE_NEIGHBOR_MARKER_LABEL, SZPLT_USER_FACE_NEIGHBOR_MARKER) && writeValue<uint32_t, false, 0>(szpltFile, m_zoneNumberLabel.c_str(), (___2677 - m_baseZone + 1)); } ___1965 faceNeighborVector; ___2039 = ___2039 && writeValue<uint64_t, false, 0>(szpltFile, USER_FACE_NEIGHBOR_COUNT_LABEL, m_userFaceNeighbors.size()); if (___2039 && m_userFaceNeighbors.size() > 0) { ___2039 = ___2039 && faceNeighborVector.alloc(m_userFaceNeighbors.size()); if (___2039) { for(size_t i = 0; i < m_userFaceNeighbors.size(); ++i) faceNeighborVector[i] = m_userFaceNeighbors[i]; ___2039 = ___2039 && ___4563<int32_t, false, 0>(szpltFile, USER_FACE_NEIGHBORS_LABEL, ___2745, m_userFaceNeighbors.size(), &faceNeighborVector[0]); } } return ___2039; } uint64_t ClassicZoneFaceNeighborWriter::sizeInFile(bool ___2002) { if (m_userFaceNeighbors.empty()) m_faceNeighborGenerator.gatherUserFaceNeighbors(m_userFaceNeighbors, ___2677); uint64_t ___3358 = 0; if (___2002) ___3358 += 2 * valueSizeInFile<uint32_t, false>(___2002); ___3358 += valueSizeInFile<uint64_t, false>(___2002); if (m_userFaceNeighbors.size() > 0) ___3358 += arraySizeInFile<int32_t, false>(m_userFaceNeighbors.size(), ___2002); return ___3358; } }}