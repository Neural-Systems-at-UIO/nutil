#include "processmanagerpcounter.h"
#include <QStringList>
#include "source/data.h"
#include <QImageReader>


float ProcessManagerPCounter::CalculateRamNeededInGB()
{
    if (m_processItems.count()==0)
        return 0;

    QSharedPointer<ProcessItem> pi = m_processItems[0];
    float singleFile = Util::getImageFileSizeInGB(m_inputDir+  pi->m_inFile +"."+pi->m_filetype);
    //    qDebug() << "Singlefile: " << singleFile;
    return singleFile*m_numProcessors*2.5; // 3 files open at the same time... around

}

void ProcessManagerPCounter::LoadXML(NutilTemplate* data)
{

    if (!QFile::exists(m_anchorFile)) {
        QDir dir(m_atlasDir);
        foreach( const QFileInfo& entry, dir.entryInfoList( QStringList() << "*.json"<<"*.xml", QDir::Files | QDir::Hidden | QDir::NoSymLinks ) ) {
           m_anchorFile = entry.absoluteFilePath();
           LMessage::lMessage.Message("Automatically assumed anchor file: "+m_anchorFile);
           break;
        }
    }


    if (QFile::exists(m_anchorFile))
        m_xmlAnchor = AnchorFactory::Load(m_anchorFile);
    //        m_xmlAnchor.Load(m_anchorFile);
    else {
        LMessage::lMessage.Message("Could not find anchor file: " + m_anchorFile + ". Please specify in the input xml file!" );
        Data::data.abort = true;
    }

    // Verify that the atlas specified in the anchor file is the same as the current run
    if (m_dataType==QUINT) {
        QString labelType = data->Get("label_file");

        if (m_xmlAnchor!=nullptr) {
            qDebug() << "*** ATLAS: " +m_xmlAnchor->m_atlas;
            if (!atlasQuickniiMap.contains(m_xmlAnchor->m_atlas)) {
                // Unknown anchoring data?
                LMessage::lMessage.Message("<font color=\"#FF0000\">Warning: unrecognized atlas map '"+m_xmlAnchor->m_atlas+"' in the anchor file. Might be a potential problem, please make sure that the atlas is correct!</font>");

            }
            else {
                if (atlasQuickniiMap[m_xmlAnchor->m_atlas]!=labelType) {

                    //LMessage::lMessage.Message("<font color=\"#FF0000\">Error: Atlas map specified in the anchor file not the same as specified in nutil. Please make sure that these are identical types. ('"+ atlasQuickniiMap[m_xmlAnchor->m_atlas]+"' from the xml anchor file vs '"+labelType +"' in Nutil)</font>");
                    //Data::data.abort = true;
                    m_overrideLabelFile = atlasQuickniiMap[m_xmlAnchor->m_atlas];
                }

            }
        }
    }

}


bool ProcessManagerPCounter::Build(NutilTemplate* data)
{
    m_processItems.clear();
    Data::data.m_globalMessage="";

    int x = 1;
    int y = 22;
    Data::data.abort = false;
    // Reset area counter
    Area::s_area_id_counter = 0;


    if (QFile::exists("version.txt")) {
        QFile::copy("version.txt",m_outputDir+"/"+"version.txt");
    }


    if (m_dataType==QUINT)
        LoadXML(data);

    if (m_pixelCutoffMax<=m_pixelCutoff) {
        LMessage::lMessage.Error("Error: max pixel cutoff cannot be lower than lower pixel cutoff.");
        m_processItems.clear();
        return false;

    }



    if (m_areaScale==(float)0) {
        LMessage::lMessage.Error("Pixel scale is not set (or is set to zero). Please specify a valid pixel scale (such as 1).");
        return false;
    }
    QStringList files;
    Util::findFilesInSubDirectories(&files,m_inputDir,"png");


    // Unique ID format

    m_regexp = "_s[0-9]*";

    if (m_patternType=="user")
        m_regexp = m_files[0];



    if (m_patternType == "_sXXX" || m_patternType=="user") {
        QRegularExpression re(m_regexp);
        QStringList newFiles;
        for (QString s: files) {
            QRegularExpressionMatch match = re.match(s);
            if (match.hasMatch()) {
                if (!s.toLower().contains("mask")) {

                    newFiles.append(match.captured(0));
                }

            }
            //            if (regExp.mat)
        }
        m_files = newFiles;
    }


    if (Data::data.abort)
        return false;


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
            if (m_dataType==QUINT) {

                QString inFlatFull = Util::findFileInDirectory(name,m_atlasDir,"flat","");
                if (inFlatFull=="") {
                    LMessage::lMessage.Error("Error: Could not find FLAT files that contains: " + name + ".");
                    m_processItems.clear();
                    return false;
                }
            }
            //            if (m_dataType=="none") {
            //              inFlatFull =  Util::RemoveFinalFiletype(inFileFull)+".flatfake";

            //        }
            QStringList l = inFileFull.split('/');
            QString inFile = l[l.length()-1];


            QString inFileSingle = inFile.split('.')[0];
            auto pi = QSharedPointer<ProcessItem>(new ProcessItem(inFileSingle, m_outputDir+ inFileSingle + ".xlsx",0, QPointF(1,1), inFileSingle, m_outputDir));
            pi->m_pixelAreaScale = m_areaScale;//*m_sheet->readNum(y,x+1);

            if (pi->m_pixelAreaScale==0) {
                LMessage::lMessage.Error("Pixel scale is not set (or is set to zero) for image file '" + name +"'. Please specify a valid pixel area scale (such as 1).");
                return false;
            }

            //qDebug() << name;
            pi->m_xmlData =m_xmlAnchor->findData(name);
            pi->m_id = name;//m_sheet->readStr(y,x+2);
            pi->m_reportName = name.split(".").first(); //m_sheet->readStr(y,x+2);
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
                LMessage::lMessage.Error("Error: Report must have unique names for : " + m_processItems[i]->m_reportName);
                return false;

            }
        }
    }


    if (m_processItems.count()==0) {
        LMessage::lMessage.Error("Error: You need to specify at least one input file. Press the help button for instructions, Nutil is currently searching for files that contain the following regular expression format: '"+m_regexp + "'. Please make sure that this format matches the IDs in your input files.");

    }

    Util::CreateDir(m_outputDir+QDir::separator()+m_reportDirectory);
    Util::CreateDir(m_outputDir+QDir::separator()+m_coordinateDirectory);
    Util::CreateDir(m_outputDir+QDir::separator()+m_imageDirectory);


    if (!QDir(m_outputDir).exists())
        QDir().mkdir(m_outputDir);



    return true;

}

void ProcessManagerPCounter::Execute()
{
    if (m_dataType==QUINT) {
        m_labels.Load(m_labelFile);
        if (m_labels.atlases.count()==0) {
            LMessage::lMessage.Error("Incorrect label file. Please check parameters in excel sheet.");
            return;
        }
        Data::data.m_isQuickNII = true;

    }
    if (m_dataType == NONE) {
        m_labels.Clear();
        m_labels.LoadFake();
        Data::data.m_isQuickNII = false;
    }
    QFile::copy(m_excelInputFilename, m_outputDir + "/" + m_excelInputFilename.split("/").last());


    Data::data.m_maskedOutColor = Qt::black;

    if (m_background==Qt::black && m_useCustomMask)  {
        Data::data.m_maskedOutColor = Qt::red;
    }


    m_processFinished = false;
    ClearProcesses();
    for (int i=0;i<m_processItems.length();i++) {
        m_processes.append(QSharedPointer<NutilProcess>(new NutilProcess()));
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
        auto pi = m_processItems[i];

        if (Data::data.abort)
            continue;

        //        qDebug() << "Pcounter: " << pi->m_inFile;

        QMatrix4x4 mat(m_processItems[i]->m_xmlData.toMatrix());

        QVector3D normal = QVector3D::crossProduct(
                    m_processItems[i]->m_xmlData.m_o-m_processItems[i]->m_xmlData.m_v,
                    m_processItems[i]->m_xmlData.m_o-m_processItems[i]->m_xmlData.m_u).normalized();


        QString maskFile = "";
        // Process masks
        if (m_useCustomMask) {

            maskFile = Util::findFileInDirectory(QStringList() << "mask" << pi->m_id,m_maskDir,"png","");
            if (maskFile==""){
                LMessage::lMessage.Error("  Could not find mask file for " +pi->m_inFile);
                Data::data.abort = true;
            }

            if (!Util::VerifyImageFileSize(maskFile,8192*2)){
                LMessage::lMessage.Error("  Mask file '" +pi->m_inFile+"' has too large dimensions! Make sure that the file size is less than 2048x2048");

                Data::data.abort = true;

            }


        }

        //        qDebug() << Data::data.abort;
        if (!Data::data.abort)
            m_processes[i]->PCounter(m_inputDir+  pi->m_inFile +"."+pi->m_filetype, m_background,m_colorThreshold, &m_processes[i]->m_areas, m_pixelCutoff, m_pixelCutoffMax, maskFile, m_customMaskInclusionColors);

        if (Data::data.abort)
            continue;

        //        LMessage::lMessage.Log("  Quantifier done for " +pi->m_inFile);
        for (Area&a : m_processes[i]->m_areas) {
            a.m_mat = mat;
            a.m_matrixInitialized = true;
            //            qDebug() << normal;
            a.m_planeNormal = normal;

        }


        //if (m_dataType=="quicknii")
        {

            m_processes[i]->m_infoText = "Anchoring areas";
            // Find atlas file:
            QString atlasFile = Util::findFileInDirectory(pi->m_id,m_atlasDir,"flat","");

            if (atlasFile=="" && m_dataType == QUINT) {
                LMessage::lMessage.Error("Could not find any atlas flat files!");
                Data::data.abort = true;
            }
            //        if (Data::data.abort)
            //          break;


            //            LMessage::lMessage.Log("Anchoring: " + pi->m_inFile);
            if (!Data::data.abort)
            {
                QVector3D col = QVector3D(m_customMaskInclusionColors.red(),m_customMaskInclusionColors.green(),m_customMaskInclusionColors.blue());
                if (m_areaSplitting!=1)
                    m_processes[i]->lImage.AnchorSingle(pi->m_inFile, atlasFile, m_outputDir + pi->m_inFile + "_test.png", m_labels, &m_processes[i]->m_counter, &m_processes[i]->m_areas, pi->m_pixelAreaScale,i, maskFile, col);
                else
                    m_processes[i]->lImage.AnchorSplitting(pi->m_inFile, atlasFile, m_outputDir + pi->m_inFile + "_test.png", m_labels, &m_processes[i]->m_counter, &m_processes[i]->m_areas, pi->m_pixelAreaScale,i, maskFile, col);

            }

            m_processItems[i]->m_atlasAreaScaled = m_processes[i]->lImage.m_totalPixelArea;
            //            LMessage::lMessage.Log("Saving image areas :"+ pi->m_inFile);
            if (!Data::data.abort)
                m_processes[i]->lImage.SaveAreasImage(m_outputDir + QDir::separator() + m_imageDirectory + QDir::separator()+m_prefix+ pi->m_inFile + ".png",&m_processes[i]->m_counter, &m_processes[i]->m_areas, reports.getList(),cols,maskFile,m_customMaskInclusionColors, m_outputRegionNumbers, m_displayLabelID);
            m_mainCounter.Tick();
        }
        m_processes[i]->m_counter.m_progress = 100;
        //        LMessage::lMessage.Log("Releasing: " + pi->m_inFile);
        //        LMessage::lMessage.Message("<a href=\"file://"+m_outputDir+"\">"+m_outputDir+"</a>");

        // 37 49 71


        m_processes[i]->ReleasePCounter();
    }

    /*


  _____                       _
 |  __ \                     | |
 | |__) |___ _ __   ___  _ __| |_ ___
 |  _  // _ \ '_ \ / _ \| '__| __/ __|
 | | \ \  __/ |_) | (_) | |  | |_\__ \
 |_|  \_\___| .__/ \___/|_|   \__|___/
            | |
            |_|


     * */


    if (!Data::data.abort)
        BuildReports();
    //    QVector<ProcessItem*> m_processItems;
    //  QVector<QSharedPointer<NutilProcess>> m_processes;
    reports = Reports();


    m_processFinished = true;
    /*    for (int i=0;i<m_processItems.count();i++)
        delete m_processItems.takeAt(i);
    for (int i=0;i<m_processes.count();i++)
        delete m_processes.takeAt(i);
*/
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



    m_inputDir = data->Get("quantifier_input_dir")+"/"; //Util::fixFolder(m_sheet->readStr(4,1));
    m_maskDir = data->Get("custom_mask_directory")+"/"; //Util::fixFolder(m_sheet->readStr(4,1));
    if (m_maskDir == "/")
        m_maskDir = m_inputDir;

    m_outputDir = data->Get("quantifier_output_dir")+"/";
    //    float col_r = m_sheet->readNum(3,1);
    //  float col_g = m_sheet->readNum(3,2);
    //float col_b = m_sheet->readNum(3,3);

    //    m_background = QColor(col_r, col_g, col_b);
    m_background =  NutilTemplateItem::StringToColor(data->Get("extraction_color"));

    m_patternType = data->Get("pattern_match");

    //    m_dataType = "quicknii";//m_sheet->readStr(19,1).toLower();
    QString analysisType = data->Get("analysis_type").toLower();
    m_dataType = NONE;
    if (analysisType=="quicknii")
        m_dataType =QUINT;
    if (analysisType=="quint")
        m_dataType =QUINT;

    m_colorThreshold = QVector3D(2,2,2);//QVector3D(m_sheet->readNum(3,4),m_sheet->readNum(3,5),m_sheet->readNum(3,6));

    //if select mouse reference atlas, automatically use the CustomRegionMouse resource file
    // this is not yet implemented for rat

    m_displayLabelID = data->Get("display_label_id").toLower()=="yes";

    m_reportSheetName = "";
    if (data->Get("custom_region_type").toLower()=="custom")
        m_reportSheetName = data->Get("custom_region_file");

    if (m_dataType == QUINT) {
        m_atlasDir = data->Get("quantifier_atlas_dir");
        m_coordinateRandomSpread = 0;//data->Get("coordinate_random_distortion").toDouble();
    }


    if (m_dataType == QUINT) {
        QString labelType = data->Get("label_file");
        if (m_overrideLabelFile!="")
            labelType = m_overrideLabelFile;
        //       qDebug() << "Labl type:" <<labelType;
        if (labelType.toLower() == "custom") {
            m_labelFile = data->Get("custom_label_file");
            //m_reportSheetName = ":Resources/CustomRegions/CustomRegionMouse_2015.xlsx";
            if (data->Get("custom_region_type").toLower()!="custom") {
                LMessage::lMessage.Message("Warning: you are using a custom label file without a custom report file.");
            }
        }
        if (labelType == "Allen Mouse Brain 2015") {
            m_labelFile = ":Resources/labels/AllenMouseBrain_Atlas_CCF_2015.label";
            if (data->Get("custom_region_type").toLower()=="default")
                m_reportSheetName = ":Resources/CustomRegions/CustomRegionMouse_2015.xlsx";
        }
        if (labelType == "Allen Mouse Brain 2017") {
            m_labelFile = ":Resources/labels/AllenMouseBrain_Atlas_CCF_2017.label";
            if (data->Get("custom_region_type").toLower()=="default")
                m_reportSheetName = ":Resources/CustomRegions/CustomRegionMouse_2017.xlsx";
        }
        if (labelType == "WHS Atlas Rat v2") {
            m_labelFile = ":Resources/labels/WHS_Atlas_Rat_Brain_v2.label";
            if (data->Get("custom_region_type").toLower()=="default")
                m_reportSheetName = ":Resources/CustomRegions/CustomRegionRat_v2.xlsx";

        }
        if (labelType == "WHS Atlas Rat v3") {
            m_labelFile = ":Resources/labels/WHS_Atlas_Rat_Brain_v3.label";
            if (data->Get("custom_region_type").toLower()=="default")
                m_reportSheetName = ":Resources/CustomRegions/CustomRegionRat_v3_v2.xlsx";

        }
        if (labelType == "WHS Atlas Rat v4") {
            m_labelFile = ":Resources/labels/WHS_Atlas_Rat_Brain_v4.label";
            if (data->Get("custom_region_type").toLower()=="default")
                m_reportSheetName = ":Resources/CustomRegions/CustomRegionRat_v4.xlsx";
           //LMessage::lMessage.Message("Warning: the implementation of WHSv4 in Nutil Quantifier has not been thoroughly tested.");
        }


    }


    m_files = data->Get("files").trimmed().simplified().split(",");

    m_pixelCutoff = data->Get("object_min_size").toFloat();
    //    m_pixelCutoffMax = data->Get("object_max_size").toFloat();
    m_pixelCutoffMax = 100000; // NOT USED!
    m_areaScale = data->Get("global_pixel_scale").toFloat();
    m_areaSplitting = data->Get("object_splitting").toLower()=="yes"?1:0;

    m_outputRegionNumbers = data->Get("output_region_id").toLower()=="no"?false:true;


    Data::data.m_hasAreaSplitting = m_areaSplitting;
    if (m_dataType==QUINT)
        m_anchorFile = data->Get("xml_anchor_file");
    m_niftiSize = data->Get("nifti_size").toInt();//m_sheet->readNum(12,1);
    m_xyzScale = data->Get("pixel_density").toInt();
    //m_units = m_sheet->readStr(10,2);
    m_units = data->Get("quantifier_pixel_scale_unit");

    m_output3DPoints = data->Get("coordinate_extraction").toLower();
    m_outputNifti = m_niftiSize!=0;
    m_customRegionType =  data->Get("custom_region_type").toLower();

    m_prefix = data->Get("name");
    if (m_prefix!="")
        m_prefix = m_prefix+"_";

    m_useCustomMask = data->Get("use_custom_masks").toLower()=="yes";
    if (m_useCustomMask)
        m_customMaskInclusionColors = NutilTemplateItem::StringToColor(data->Get("custom_mask_color"));

    if (data->Get("output_report").toLower()=="all")
        m_reportType = REPORTTYPE_ALL;
    if (data->Get("output_report").toLower()=="none")
        m_reportType = REPORTTYPE_NONE;


    m_outputFileType = data->Get("output_report_type").toLower();
    /*    if (!(m_outputFileType.toLower()=="xlsx" || m_outputFileType.toLower()=="csv")) {
        LMessage::lMessage.Error("Error: report type must be specified (xlsx or csv).");
        Data::data.abort = true;
        return;
    }
*/


    if (m_dataType != QUINT) {
        m_output3DPoints = "no";
        m_outputNifti = false;
    }


    if (m_pixelCutoffMax<m_pixelCutoff) {

    }



    if (m_dataType == QUINT)

        if (QFile::exists(m_reportSheetName)) {

            if (!m_reportSheetName.toLower().endsWith(".xlsx")) {
                LMessage::lMessage.Error("Error: custom region file must be xlsx");
                Data::data.abort = true;
                return;
            }

            LBook* sbook = new LBookXlnt();
            if (QFile::exists("temp.xlsx"))
                QFile::remove("temp.xlsx");

            QFile::copy(m_reportSheetName,"temp.xlsx");
#ifdef _WIN32
            QFile f("temp.xlsx");
            f.setPermissions(QFile::ReadOther | QFile::WriteOther);
#endif
            sbook->Load("temp.xlsx");
            QFile::remove("temp.xlsx");

            QSharedPointer<LSheet> reportSheet = sbook->GetSheet(0);
            if (reportSheet == nullptr) {
                LMessage::lMessage.Error("Error: could not find any report sheet in the excel file!");
                Data::data.abort = true;
                return;
            }
            else
                GenerateReports(reportSheet);

        }
    if (m_dataType==NONE) {
        reports.m_reports.push_back(Report("Report", QStringList() << "1", m_background));
        for (Report& r: reports.m_reports)
            r.m_unit = m_units;


    }


    if (m_dataType == QUINT) {
        QString labelType = data->Get("label_file");

        if (labelType == "WHS Atlas Rat v4") {
            LMessage::lMessage.Message("<font color=\"#FF0000\">Warning: the implementation of WHSv4 in Nutil Quantifier has not been thoroughly tested.</font>");
        }
    }


}

void ProcessManagerPCounter::SetupFakeReports()
{

}

void ProcessManagerPCounter::CleanupFakeReports()
{

}

void ProcessManagerPCounter::BuildReports()
{


    QString RefAtlasname = "RefAtlasRegions.xlsx";
    if (m_dataType != QUINT) {
        RefAtlasname = "Regions.xlsx";
    }
    if (m_reportType!=REPORTTYPE_NONE) {

        reports.CreateCustomRegions(m_outputDir + QDir::separator() + m_reportDirectory + QDir::separator()+m_prefix+"CustomRegions.xlsx", m_processes, m_processItems, &m_labels,m_outputFileType);
        if (m_customRegionType=="custom" || m_customRegionType=="default") {
            reports.CreateBook(m_outputDir + QDir::separator() + m_reportDirectory + QDir::separator()+ m_prefix+"CustomRegions.xlsx", m_outputFileType);
            reports.CreateSheets(m_processes, &m_labels, m_units, m_areaSplitting==1.0);
        }
        if (m_areaSplitting == 0.0)
            reports.CreateSliceReports(m_outputDir + QDir::separator() + m_reportDirectory + QDir::separator()+m_prefix+"Objects.xlsx", m_processes, m_processItems, &m_labels, m_units,m_outputFileType,m_displayLabelID);

        reports.CreateRefAtlasRegionsSlices(m_outputDir + QDir::separator() + m_reportDirectory + QDir::separator()+m_prefix+RefAtlasname, &m_labels,m_processes, m_processItems, m_units, m_outputFileType,m_displayLabelID);
        reports.CreateRefAtlasRegions(m_outputDir + QDir::separator() + m_reportDirectory + QDir::separator()+m_prefix+RefAtlasname, &m_labels,m_processes, m_processItems, m_units, m_outputFileType);
    }

    if (m_output3DPoints=="all") {
        reports.Create3DSummaryJson(m_outputDir + QDir::separator() + m_coordinateDirectory + QDir::separator()+m_prefix+"3D_combined.json", m_processes, m_processItems, m_xyzScale,m_coordinateRandomSpread);
        reports.Create3DSliceJson(m_outputDir + QDir::separator() + m_coordinateDirectory + QDir::separator()+m_prefix+"3D_slice_", m_processes, m_processItems, m_xyzScale,m_coordinateRandomSpread);
    }
    if (m_output3DPoints=="summary") {
        reports.Create3DSummaryJson(m_outputDir + QDir::separator() + m_coordinateDirectory + QDir::separator()+m_prefix+"3D_combined.json", m_processes, m_processItems, m_xyzScale,m_coordinateRandomSpread);
    }
    if (m_output3DPoints=="slices") {
        reports.Create3DSliceJson(m_outputDir + QDir::separator() + m_coordinateDirectory + QDir::separator()+m_prefix+"3D_slice_", m_processes, m_processItems, m_xyzScale,m_coordinateRandomSpread);
    }

    //  m_infoText = "Creating 3D point cloud";
    Data::data.m_globalMessage = "Creating NIFTI";

    if (m_outputNifti)
        reports.CreateNifti(m_outputDir + "test.nii", m_processes, m_processItems, m_niftiSize);

}

void ProcessManagerPCounter::GenerateReports(QSharedPointer<LSheet> m_sheet)
{
    int i = 0;
    bool hasNext = true;
    int x = 1;
    // As long as a next one exist (x-axis reports)
    while (hasNext) {
        //        qDebug() << "Starting..:";
        QString excelName = m_sheet->readStr(i,x);
        //             qDebug() << excelName << i << " " << x;
        //           qDebug() << m_sheet->readStr(i+1,x);
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

            LMessage::lMessage.Message("Found report: <font color=\"" + reportColor.name()+"\">" +excelName+"</font> ( " + QString::number(ids.count()) + " ids )");

            //qDebug() << excelName << " , " << ids;

        }
        else hasNext = false;
        x++;
    }

    for (Report& r: reports.m_reports)
        r.m_unit = m_units;

    //    qDebug() << "DONE reading excel sheet";
}


