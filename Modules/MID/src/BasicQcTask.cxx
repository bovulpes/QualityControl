// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

///
/// \file   BasicQcTask.cxx
/// \author My Name
///

#include <TCanvas.h>
#include <TH1.h>

#include "QualityControl/QcInfoLogger.h"
#include "MID/BasicQcTask.h"

#include "Framework/DataRefUtils.h"
#include "DataFormatsMID/ColumnData.h"

namespace o2::quality_control_modules::mid
{

BasicQcTask::~BasicQcTask()
{
  if (mDetElemID) {
    delete mDetElemID;
  }
}

void BasicQcTask::initialize(o2::framework::InitContext& /*ctx*/)
{
  ILOG(Info) << "initialize BasicQcTask" << ENDM; // QcInfoLogger is used. FairMQ logs will go to there as well.

  // this is how to get access to custom parameters defined in the config file at qc.tasks.<task_name>.taskParameters
  if (auto param = mCustomParameters.find("myOwnKey"); param != mCustomParameters.end()) {
    ILOG(Info) << "Custom parameter - myOwnKey: " << param->second << ENDM;
  }

  mDetElemID = new TH1F("mDetElemID", "ID of detector element", 80, 0, 80);
  getObjectsManager()->startPublishing(mDetElemID);
  try {
    getObjectsManager()->addMetadata(mDetElemID->GetName(), "custom", "34");
  } catch (...) {
    // some methods can throw exceptions, it is indicated in their doxygen.
    // In case it is recoverable, it is recommended to catch them and do something meaningful.
    // Here we don't care that the metadata was not added and just log the event.
    ILOG(Warning) << "Metadata could not be added to " << mDetElemID->GetName() << ENDM;
  }
}

void BasicQcTask::startOfActivity(Activity& /*activity*/)
{
  ILOG(Info) << "startOfActivity" << ENDM;
  mDetElemID->Reset();
}

void BasicQcTask::startOfCycle()
{
  ILOG(Info) << "startOfCycle" << ENDM;
}

void BasicQcTask::monitorData(o2::framework::ProcessingContext& ctx)
{
  auto msg = ctx.inputs().get("digits");
  gsl::span<const o2::mid::ColumnData> patterns = o2::framework::DataRefUtils::as<const o2::mid::ColumnData>(msg);

}

void BasicQcTask::endOfCycle()
{
  ILOG(Info) << "endOfCycle" << ENDM;
}

void BasicQcTask::endOfActivity(Activity& /*activity*/)
{
  ILOG(Info) << "endOfActivity" << ENDM;
}

void BasicQcTask::reset()
{
  // clean all the monitor objects here

  ILOG(Info) << "Resetting the histogram" << ENDM;
  mDetElemID->Reset();
}

} // namespace o2::quality_control_modules::mid
