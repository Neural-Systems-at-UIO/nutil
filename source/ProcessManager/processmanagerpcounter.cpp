#include "processmanagerpcounter.h"
#include <QStringList>
#include "source/data.h"
#include <QImageReader>


float ProcessManagerPCounter::CalculateRamNeededInGB()
{
    if (m_processItems.count()==0)
        return 0;

    ProcessItem* pi = m_processItems[0];
    float singleFile = Util::getImageFileSizeInGB(m_inputDir+  pi->m_inFile +"."+pi->m_filetype);
//    qDebug() << "Singlefile: " << singleFile;
    return singleFile*m_numProcessors*2.5; // 3 files open at the same time... around

}

void ProcessManagerPCounter::LoadXML()
{

    if (QFile::exists(m_anchorFile))
        m_xmlAnchor.Load(m_anchorFile);
    else {
        LMessage::lMessage.Message("Could not find anchor file: " + m_anchorFile + ". Please specify in the input xml file!" );
        Data::data.abort = true;
    }

}


bool ProcessManagerPCounter::Build(NutilTemplate* data)
{

    m_processItems.clear();
    Data::data.m_globalMessage="";

    int x = 1;
    int y = 22;
    Data::data.abort = false;


    if (m_dataType=="quicknii")
        LoadXML();

    if (m_pixelCutoffMax<=m_pixelCutoff) {
        LMessage::lMessage.Error("Error: max pixel cutoff cannot be lower than lower pixel cutoff! ");
        m_processItems.clear();
        return false;

    }
    if (m_areaScale==0) {
        LMessage::lMessage.Error("Global pixel scale is not set (or is set to zero). Please specify a valid global pixel scale (such as 1).");
        return false;
    }
    QStringList files;
    Util::findFilesInSubDirectories(&files,m_inputDir,"png");



    QString regexp = "_s[0-9]*";

    if (m_patternType=="user")
        regexp = m_files[0];

/*    if (m_patternType=="files") {

    }*/

    if (m_patternType == "sXXX") {

        QRegularExpression re(regexp);
        QStringList newFiles;
        for (QString s: files) {
            QRegularExpressionMatch match = re.match(s);
            if (match.hasMatch()) {

                newFiles.append(match.captured(0));

            }
//            if (regExp.mat)
        }
        m_files = newFiles;
    }




//    bool done = false;
    //while (!done) {

    for (auto name: m_files) {
        name = name.trimmed();
  //      QString name = m_sheet->readStr(y,x);
//        QString name = "NOT IMPLEMENTED YET";
        if (name!="") {
            bool isTiff = false;
            QString inFileFull = Util::findFileInDirectory(name,m_inputDir,"png","mask");
            if (inFileFull=="") {
                inFileFull = Util::findFileInDirectory(name,m_inputDir,"tif","mask");
                if (inFileFull!="")
                    isTiff = true;
            }



            if (inFileFull=="") {
                LMessage::lMessage.Error("Error: Could not find file that contains: " + name);
                m_processItems.clear();
                return false;
            }
            if (m_dataType=="quicknii") {

                QString inFlatFull = Util::findFileInDirectory(name,m_atlasDir,"flat","");
                if (inFlatFull=="") {
                    LMessage::lMessage.Error("Error: Could not find FLAT files that contains: " + name + ". Did you remember to run the java binary file converter?");
                    m_processItems.clear();
                    return false;
                }
            }
            QStringList l = inFileFull.split('/');
            QString inFile = l[l.length()-1];


            QString inFileSingle = inFile.split('.')[0];
            ProcessItem* pi = new ProcessItem(inFileSingle, m_outputDir+ inFileSingle + ".xlsx",0, QPointF(1,1), inFileSingle, m_outputDir);
            pi->m_pixelAreaScale = m_areaScale;//*m_sheet->readNum(y,x+1);

            if (pi->m_pixelAreaScale==0) {
                LMessage::lMessage.Error("Pixel area scale is not set (or is set to zero) for image file '" + name +"'. Please specify a valid pixel area scale (such as 1).");
                return false;
            }


            //qDebug() << name;
            pi->m_xmlData =m_xmlAnchor.findData(name);
            pi->m_id = name;//m_sheet->readStr(y,x+2);
            pi->m_reportName = name.split(".").first() + "r"; //m_sheet->readStr(y,x+2);
//            if (pi->m_reportName=="")  pi->m_reportName = QString::number(m_sheet->readNum(y,x+2));

            if (isTiff)
                pi->m_filetype = "tif";

            m_processItems.append(pi);
        }
        y++;
    }

    // Verify IDs

    for (int i=0; i<m_processItems.count();i++) {
        if (m_processItems[i]->m_reportName.length()>24) {
            LMessage::lMessage.Error("Error: ID needs to be less than 24 characters :" + m_processItems[i]->m_id);
            return false;

        }
        if (m_processItems[i]->m_reportName=="") {
            LMessage::lMessage.Error("Error: ID needs to be not zero on x,y:" + QString::number(x) + ", " + QString::number(y));
            return false;

        }
        for (int j=i+1;j<m_processItems.count();j++) {
            if (m_processItems[j]->m_reportName.toLower()==m_processItems[i]->m_reportName.toLower()) {
                LMessage::lMessage.Error("Error: Reports have to have unique names for : " + m_processItems[i]->m_reportName);
                return false;

            }
        }
    }


    if (m_processItems.count()==0) {
        LMessage::lMessage.Error("Error: You need to specify at least one input file. See the included excel template for instructions. ");

    }

    Util::CreateDir(m_outputDir+QDir::separator()+m_reportDirectory);
    Util::CreateDir(m_outputDir+QDir::separator()+m_coordinateDirectory);
    Util::CreateDir(m_outputDir+QDir::separator()+m_imageDirectory);


    return true;

}

void ProcessManagerPCounter::Execute()
{
    if (m_dataType=="quicknii") {
        m_labels.Load(m_labelFile);
        if (m_labels.atlases.count()==0) {
            LMessage::lMessage.Error("Incorrect label file. Please check parameters in excel sheet.");
            return;
        }
    }
    QFile::copy(m_excelInputFilename, m_outputDir + "/" + m_excelInputFilename.split("/").last());

    m_processFinished = false;
    ClearProcesses();
    for (int i=0;i<m_processItems.length();i++) {
        m_processes.append(new NutilProcess());
    }
    SetParameters();

    if (m_processes.length()==0)
        return;

    Util::globalTimer.restart();
    m_mainCounter = Counter(m_processes.length(),"",false);

//    qDebug()<<"Number reports found: " << reports.m_reports.count();


    QVector<QColor> cols;
    for (int i=0;i<reports.m_reports.count();i++)
        cols.append(reports.m_reports[i].m_color);

    Data::data.m_currentPath = m_outputDir;



#pragma omp parallel for num_threads(m_numProcessors)
    for (int i=0;i<m_processes.length();i++) {
        ProcessItem* pi = m_processItems[i];


//        qDebug() << "Pcounter: " << pi->m_inFile;

        QMatrix4x4 mat(m_processItems[i]->m_xmlData.toMatrix());



        QString maskFile = "";
        if (m_useCustomMask) {

  //          qDebug() << "Search for mask file" << pi->m_id;
            maskFile = Util::findFileInDirectory(QStringList() << "mask" << pi->m_id,m_inputDir,"png","");
            if (maskFile==""){
                LMessage::lMessage.Error("  Could not find mask file for " +pi->m_inFile);
                Data::data.abort = true;
            }


//            QImageReader reader(maskFile);
            if (!Util::VerifyImageFileSize(maskFile,2048)){
                LMessage::lMessage.Error("  Mask file '" +pi->m_inFile+"' has too large dimensions! Make sure that the file size is less than 2048x2048");

                Data::data.abort = true;

            }


        }


        if (!Data::data.abort)
            m_processes[i]->PCounter(m_inputDir+  pi->m_inFile +"."+pi->m_filetype, m_background,m_colorThreshold, &m_processes[i]->m_areas, m_pixelCutoff, m_pixelCutoffMax, maskFile, m_customMaskInclusionColors);

        LMessage::lMessage.Log("  Quantifier done for " +pi->m_inFile);
        for (Area&a : m_processes[i]->m_areas)
            a.m_mat = mat;


        if (m_dataType=="quicknii") {

            m_processes[i]->m_infoText = "Anchoring areas";
            // Find atlas file:
            QString atlasFile = Util::findFileInDirectory(pi->m_id,m_atlasDir,"flat","");

            if (atlasFile=="") {
                LMessage::lMessage.Error("Could not find any atlas flat file!");
                Data::data.abort = true;
            }
            //        if (Data::data.abort)
            //          break;


            LMessage::lMessage.Log("Anchoring: " + pi->m_inFile);
            if (!Data::data.abort)
            {
                QVector3D col = QVector3D(m_customMaskInclusionColors.red(),m_customMaskInclusionColors.green(),m_customMaskInclusionColors.blue());
                if (m_areaSplitting!=1)
                    m_processes[i]->lImage.AnchorSingle(pi->m_inFile, atlasFile, m_outputDir + pi->m_inFile + "_test.png", m_labels, &m_processes[i]->m_counter, &m_processes[i]->m_areas, pi->m_pixelAreaScale,i, maskFile, col);
                else
                    m_processes[i]->lImage.AnchorSplitting(pi->m_inFile, atlasFile, m_outputDir + pi->m_inFile + "_test.png", m_labels, &m_processes[i]->m_counter, &m_processes[i]->m_areas, pi->m_pixelAreaScale,i, maskFile, col);

            }

            m_processItems[i]->m_atlasAreaScaled = m_processes[i]->lImage.m_totalPixelArea;
            LMessage::lMessage.Log("Saving image areas :"+ pi->m_inFile);
            if (!Data::data.abort)
                m_processes[i]->lImage.SaveAreasImage(m_outputDir + QDir::separator() + m_imageDirectory + QDir::separator()+ pi->m_inFile + ".png",&m_processes[i]->m_counter, &m_processes[i]->m_areas, reports.getList(),cols);
            m_mainCounter.Tick();
        }
        m_processes[i]->m_counter.m_progress = 100;
        LMessage::lMessage.Log("Releasing: " + pi->m_inFile);
        //        LMessage::lMessage.Message("<a href=\"file://"+m_outputDir+"\">"+m_outputDir+"</a>");

        // 37 49 71


        m_processes[i]->ReleasePCounter();
    }

    if (!Data::data.abort)
    {
        if (m_reportType!="none") {
            // Custom region
            reports.CreateBook(m_outputDir + QDir::separator() + m_reportDirectory + QDir::separator()+ "CustomRegionsSummary.xlsx", m_outputFileType);
            reports.CreateSheets(m_processes, &m_labels, m_units, m_areaSplitting==1.0);

            if (m_reportType=="all") {
                if (m_areaSplitting==0.0)
                    reports.CreateSliceReports(m_outputDir + QDir::separator() + m_reportDirectory + QDir::separator()+"Objects.xlsx", m_processes, m_processItems, &m_labels, m_units,m_outputFileType);

                reports.CreateSliceReportsSummary(m_outputDir + QDir::separator() + m_reportDirectory + QDir::separator()+"CustomRegionsSections.xlsx", m_processes, m_processItems, &m_labels,m_outputFileType);
                reports.CreateCombinedList(m_outputDir + QDir::separator() + m_reportDirectory + QDir::separator()+"RefAtlasRegions.xlsx", &m_labels,m_processes, m_processItems, m_units, m_outputFileType);
            }
            //        reports.Create3DSummary(m_outputDir + "3D_combined.txt", m_processes, m_processItems, m_xyzScale);
            //    m_processes[i].m_infoText = "Creating 3D point cloud";
        }

        if (m_output3DPoints=="all") {
            reports.Create3DSummaryJson(m_outputDir + QDir::separator() + m_coordinateDirectory + QDir::separator()+"3D_combined.json", m_processes, m_processItems, m_xyzScale);
            reports.Create3DSliceJson(m_outputDir + QDir::separator() + m_coordinateDirectory + QDir::separator()+"3D_slice_", m_processes, m_processItems, m_xyzScale);
        }
        if (m_output3DPoints=="summary") {
            reports.Create3DSummaryJson(m_outputDir + QDir::separator() + m_coordinateDirectory + QDir::separator()+"3D_combined.json", m_processes, m_processItems, m_xyzScale);
        }
        if (m_output3DPoints=="slices") {
            reports.Create3DSliceJson(m_outputDir + QDir::separator() + m_coordinateDirectory + QDir::separator()+"3D_slice_", m_processes, m_processItems, m_xyzScale);
        }


        //  m_infoText = "Creating 3D point cloud";
        Data::data.m_globalMessage = "Creating NIFTI";

        if (m_outputNifti)
            reports.CreateNifti(m_outputDir + "test.nii", m_processes, m_processItems, m_niftiSize);


    }
//    QVector<ProcessItem*> m_processItems;
  //  QVector<NutilProcess*> m_processes;
    reports = Reports();


    m_processFinished = true;
    for (int i=0;i<m_processItems.count();i++)
        delete m_processItems.takeAt(i);
    for (int i=0;i<m_processes.count();i++)
        delete m_processes.takeAt(i);

    m_processItems.clear();
    m_processes.clear();


}




void ProcessManagerPCounter::ReadHeader(NutilTemplate* data)
{
    /*
    type;  Type: ;  string; Quantifier
    name; Name: ; string;
    input_dir; Input directory; directory;
    output_dir; Output directory; directory;
    atlas_dir; Atlas directory; directory;
    label_file; Label file; file;
    xml_anchor_file; XML anchor file; file;
    object_splitting; Object splotting; list; yes, no; yes
    object_min_size; Object minimum size; number; 8
    object_max_size; Object maximum size; number; 10000
    global_pixel_scale; Global scale; number; 1
    custom_region_file; Custom region file; file;
    use_custom_masks; Use custom masks; list; yes, no; no
    custom_mask_color ; Custom mask color ; color ; 255,255,255,255
    output_report; Output reports; list; all, summary,none; all
    output_report_type; Output report type; list; xlsx, csv
*/



    m_inputDir = data->Get("input_dir")+"/"; //Util::fixFolder(m_sheet->readStr(4,1));
    m_outputDir = data->Get("output_dir")+"/";
//    float col_r = m_sheet->readNum(3,1);
  //  float col_g = m_sheet->readNum(3,2);
    //float col_b = m_sheet->readNum(3,3);

//    m_background = QColor(col_r, col_g, col_b);
    m_background =  NutilTemplateItem::StringToColor(data->Get("extraction_color"));

    m_patternType = data->Get("pattern_match");

    m_dataType = "quicknii";//m_sheet->readStr(19,1).toLower();


    m_colorThreshold = QVector3D(2,2,2);//QVector3D(m_sheet->readNum(3,4),m_sheet->readNum(3,5),m_sheet->readNum(3,6));
    if (m_dataType=="quicknii")
       m_atlasDir = data->Get("atlas_dir");
    if (m_dataType=="quicknii") {
       QString labelType = data->Get("label_file");
//       qDebug() << "Labl type:" <<labelType;
       if (labelType == "Allen Mouse Brain 2015")
            m_labelFile = ":Resources/labels/AllenMouseBrain_Atlas_CCF_2015.label";
       if (labelType=="WHS Atlas Rat v2")
           m_labelFile = ":Resources/labels/WHS_Atlas_Rat_Brain_v2.label";
       if (labelType=="WHS Atlas Rat v3")
           m_labelFile = ":Resources/labels/WHS_Atlas_Rat_Brain_v3.label";
    }


    m_files = data->Get("files").trimmed().simplified().split(",");

    m_pixelCutoff = data->Get("object_min_size").toFloat();
    m_pixelCutoffMax = data->Get("object_max_size").toFloat();
    m_areaScale = data->Get("global_pixel_scale").toFloat();
    m_areaSplitting = data->Get("object_splitting").toLower()=="yes"?1:0;
    if (m_dataType=="quicknii")
        m_anchorFile = data->Get("xml_anchor_file");
    m_niftiSize = data->Get("nifti_size").toInt();//m_sheet->readNum(12,1);
    //m_xyzScale = m_sheet->readNum(13,1);
    m_reportSheetName = data->Get("custom_region_file");
    //m_units = m_sheet->readStr(10,2);

    m_output3DPoints = data->Get("coordinate_extraction").toLower();
    m_outputNifti = m_niftiSize!=0;


    m_useCustomMask = data->Get("use_custom_mask").toLower()=="yes";
    if (m_useCustomMask)
        m_customMaskInclusionColors = NutilTemplateItem::StringToColor(data->Get("custom_mask_color"));

    m_reportType = data->Get("output_report");

    m_outputFileType = data->Get("output_report_type");;
//    qDebug() << "Output type: " <<m_outputFileType;
    if (!(m_outputFileType.toLower()=="xlsx" || m_outputFileType.toLower()=="csv")) {
        LMessage::lMessage.Error("Error: report type must be specified (xlsx or csv). Are you sure you are using the correct template version?");
        Data::data.abort = true;
        return;
    }



    if (m_pixelCutoffMax<m_pixelCutoff) {

    }
//    qDebug() << "HERE";

    LBook* sbook = new LBookXlnt();
    sbook->Load(m_reportSheetName);
    LSheet* reportSheet = sbook->GetSheet(0);
    if (reportSheet == nullptr) {
        LMessage::lMessage.Error("Error: could not find any report sheet in the excel file!");
        Data::data.abort = true;
        return;
    }
    else
        GenerateReports(reportSheet);
//*/

}

void ProcessManagerPCounter::GenerateReports(LSheet *m_sheet)
{
    bool found = false;
    int i = 0;
/*    qDebug() << "Generating reports..";
    // Find hierarchy analysis list
    while ((i<1000) && (found==false)) {
        i++;
        QString t = m_sheet->readStr(i,0);
        if (t.simplified().toLower() == "hierarchy analysis list") {
            found = true;
            break;
        }
    }
    i++;*/
    i=0;
    bool hasNext = true;
    int x = 1;
    qDebug() << "Reading from report sheet";
    // As long as a next one exist (x-axis reports)
    while (hasNext) {
        QString excelName = m_sheet->readStr(i,x);
//        qDebug() << excelName << i << " " << x;
        if (excelName.simplified()!="") {
            QColor reportColor = m_sheet->readCol(i+1,x);

            QStringList ids;// = QString::fromWCharArray(m_sheet->readStr(i,3)).split(',');
            bool done = false;
            int j=i+3;
            while (!done) {
                long num = m_sheet->readNum(j,x);
                QString s = QString::number(num);
                if (s!="" && s!="0" && j<1024)
                    ids<<s;
                else
                    done = true;
                j++;
            }


            reports.m_reports.push_back(Report(excelName, ids,reportColor));

            //LMessage::lMessage.Message("Found report: <font color=\"" + reportColor.name()+"\">" +excelName+"</font> ( " + QString::number(ids.count()) + " ids )");

            //qDebug() << excelName << " , " << ids;

        }
        else hasNext = false;
        x++;
    }

    for (Report& r: reports.m_reports)
        r.m_unit = m_units;
}


