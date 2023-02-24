#include "processmanagervolumiser.h"
#include <QStringList>
#include "source/data.h"
#include <QImageReader>
#include <QProcessEnvironment>



QVector<QColor> ProcessManagerVolumiser::getPalette(QString pal)
{
    QVector<QColor> colors;
    colors.resize(m_sections);
    if (pal=="default") {
        for (int i=0;i<colors.count();i++) {
            float t = i/(float)colors.count();
            colors[i].setRed(t*255);
            colors[i].setBlue((1-t)*255);
            colors[i].setGreen((exp(-pow(t-0.5,2)*30))*255);
        }
    }
    if (pal=="plasma") {
        for (int i=0;i<colors.count();i++) {
            float t = i/(float)colors.count();
            colors[i].setRed((t+0.5)*255);
            colors[i].setBlue((t/2+0.5)*255);
            colors[i].setGreen((exp(-pow(t-0.5,2)*20))*255);

//            colors[i].setGreen((exp(-pow(t-0.5,2)*30))*255);
        }
    }
    return colors;
}

void ProcessManagerVolumiser::Volumise(QString filename, QSharedPointer<ProcessItem> item, QString flatFile)
{
    QString o ="";
    //    o+="{\n";
    //  o+="\"atlas_type\" : \""+atlasType+"\",\n";

    //    for (int i=0;i<m_reports.count();i++)
    //      k+=m_reports[i].m_areasOfInterest.count();


    int tcount = 0;



    QImage img(m_inputDir+filename);
  //  qDebug() << filename;
    // First generate 3d coordinates
    int split = m_sections;
    QMap<int,QVector<QPoint>> mPoints;

    QVector<QColor> colors = getPalette(m_palette);
    qDebug() << colors.count();

    int umax = -1;
    int umin = 255;
    //scale
    Flat2D refImg;
    refImg.Load(flatFile);

    for (int y=0;y<img.height();y++)
        for (int x=0;x<img.width();x++){

            int f = (refImg.pixel(x/(double)img.width()*refImg.width(),
                                    y/(double)img.height()*refImg.height() ));
            if (f>0) {
                uchar c= (img.pixelColor(x,y).red());
                if (c>umax) umax=c;
                if (c<umin) umin=c;
            }

        }

    int usize = umax-umin;
    for (int y=0;y<img.height();y++)
        for (int x=0;x<img.width();x++) {
            uchar u = (img.pixelColor(x,y).red()-umin)/(float)usize*split;
            int f = (refImg.pixel(x/(double)img.width()*refImg.width(),
                                    y/(double)img.height()*refImg.height() ));
            if (f>0)
            {
                mPoints[u].append(QPoint(x,y));
            }
        }
    o+="[\n";
    float scale = 8.0;
    int count = 0;//m_reports[i].m_areasOfInterest.count();

    for (int i=0;i<mPoints.keys().length();i++) {
        auto lst = mPoints[i];
        QColor c = colors[i%split];
        o+="\n";
        //    if (cnt!=0) o+=",\n";
        o+="{\"idx\":"+QString::number(lst.length())+",\"count\":"+QString::number((int)(count))+",";
        o+="\n";

        o+="\"r\":" + QString::number(c.red()) + ",\"g\":" + QString::number(c.green()) + ",\"b\":" + QString::number(c.blue()) + ",\"name\":\""+ QString::number(i)+ "\",";
        o+="\n";

        o+="\"triplets\":[";
        CoordinateTransform transform(item->m_xmlData);
        for (auto& p : lst) {
            //            if (cnt!=0) o+=",";

            QVector3D v( p.x()/(double)img.width()*transform.m_xmlData->m_width,
                         p.y()/(double)img.height()*transform.m_xmlData->m_height,1);


            v = transform.getProjection(v);

            o+=QString::number(v.x())+ ","+QString::number(v.y())+","+QString::number(v.z());
            nifti.SetRGBPixel(v/m_niftiScale,c);
            auto sz = nifti.header.dim[2];

            if (lst.last()!=p)
                o+=",";
        }
        o+="]}";
        if (i!=mPoints.keys().length()-1)
            o+=",";

    }


    o+="\n]\n";
    Util::SaveTextFile(m_outputDir+"/3d"+item->m_id+".json",o);
}


bool ProcessManagerVolumiser::Build(NutilTemplate* data)
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


    //    qDebug() << "HERE" << m_atlasDir;

    LoadXML(data);

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
        }
        m_files = newFiles;
    }


    if (Data::data.abort)
        return false;


    //    bool done = false;
    //while (!done) {
//    nifti.Create(m_xmlAnchor->m_target_resolution/m_niftiScale,Nifti::DataType::DT_UNSIGNED_CHAR, 8);
    nifti.Create(m_xmlAnchor->m_target_resolution/m_niftiScale,Nifti::DataType::DT_RGB, 24);
 //   nifti.Load("/Users/leuat/Downloads/WHS_SD_rat_atlas_v4_pack/WHS_SD_rat_atlas_v4.nii");
    for (auto name: m_files) {
        name = name.trimmed();
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

            QString inFlatFull = Util::findFileInDirectory(name,m_atlasDir,"flat","");
            QString inSegFull = Util::findFileInDirectory(name,m_atlasDir,"seg","");
            if (inFlatFull == "" && inSegFull == "") {
                LMessage::lMessage.Error("Error: Could not find FLAT/SEG files that contains: " + name + ".");
                m_processItems.clear();
                return false;
                //                qDebug() << inSegFull;

                // Prioritise seg files
                if (inSegFull!="")
                    inFlatFull = inSegFull;
            }
            //            if (m_dataType=="none") {
            //              inFlatFull =  Util::RemoveFinalFiletype(inFileFull)+".flatfake";

            //        }
            QStringList l = inFileFull.split('/');
            QString inFile = l[l.length()-1];


            QString inFileSingle = inFile.split('.')[0];
            auto pi = QSharedPointer<ProcessItem>(new ProcessItem(inFileSingle, m_outputDir+ inFileSingle + ".xlsx",0, QPointF(1,1), inFileSingle, m_outputDir));
            pi->m_pixelAreaScale = m_areaScale;//*m_sheet->readNum(y,x+1);


            //qDebug() << name;
            pi->m_xmlData =m_xmlAnchor->findData(name);
            pi->m_id = name;//m_sheet->readStr(y,x+2);
            pi->m_reportName = name.split(".").first(); //m_sheet->readStr(y,x+2);
            //            if (pi->m_reportName=="")  pi->m_reportName = QString::number(m_sheet->readNum(y,x+2));

            pi->m_inFile = inFile;


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




    return true;

}

void ProcessManagerVolumiser::Execute()
{
    m_labels.Load(m_labelFile);
    if (m_labels.atlases.count()==0) {
        LMessage::lMessage.Error("Incorrect label file. Please check parameters in excel sheet.");
        return;
    }



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

    StartTimer();
#pragma omp parallel for num_threads(m_numProcessors)
    for (int i=0;i<m_processes.length();i++) {
        auto pi = m_processItems[i];

        if (Data::data.abort)
            continue;

        //        qDebug() << omp_get_thread_num() << omp_get_thread_num();

              qDebug() << "Volumiser: " << pi->m_inFile;

        QMatrix4x4 mat(m_processItems[i]->m_xmlData.toMatrix());

        QVector3D normal = QVector3D::crossProduct(
                    m_processItems[i]->m_xmlData.m_o-m_processItems[i]->m_xmlData.m_v,
                    m_processItems[i]->m_xmlData.m_o-m_processItems[i]->m_xmlData.m_u).normalized();


        {

            m_processes[i]->m_infoText = "Volumising";
            // Find atlas file:
            QString atlasFile = Util::findFileInDirectory(pi->m_id,m_atlasDir,"flat","");
            QString atlasFileSeg = Util::findFileInDirectory(pi->m_id,m_atlasDir,"seg","");
            if (atlasFileSeg!="")
                atlasFile = atlasFileSeg;



            Volumise(m_processItems[i]->m_inFile,m_processItems[i],atlasFile);

 //           m_processItems[i]->m_atlasAreaScaled = m_processes[i]->lImage.m_totalPixelArea;
            m_mainCounter.Tick();
        }
        m_processes[i]->m_counter.m_progress = 100;
        //        LMessage::lMessage.Log("Releasing: " + pi->m_inFile);
        //        LMessage::lMessage.Message("<a href=\"file://"+m_outputDir+"\">"+m_outputDir+"</a>");

        // 37 49 71


        //        m_processes[i]->ReleasePCounter();
    }
    EndTimer("Quantifying");
    qDebug() << "Finishing up";

    m_processFinished = true;
    /*    for (int i=0;i<m_processItems.count();i++)
        delete m_processItems.takeAt(i);
    for (int i=0;i<m_processes.count();i++)
        delete m_processes.takeAt(i);
*/
    m_processItems.clear();
    m_processes.clear();
    nifti.Save(m_outputDir+"/volume.nii");

    qDebug() << "Done";
}




void ProcessManagerVolumiser::ReadHeader(NutilTemplate* data)
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

    m_atlasDir = data->Get("quantifier_atlas_dir");
    m_outputDir = data->Get("quantifier_output_dir");
    if (m_outputDir.trimmed()=="") {
        LMessage::lMessage.Error("Error: output directory not specified. ");
        Data::data.abort = true;
        return;

    }
    m_outputDir+="/";
    m_palette = data->Get("palette");
    m_sections = data->GetInt("sections");
    if (!QDir(m_outputDir).exists())
        QDir().mkdir(m_outputDir);

/*    Util::CreateDir(m_outputDir+QDir::separator()+m_reportDirectory);
    Util::CreateDir(m_outputDir+QDir::separator()+m_coordinateDirectory);
    Util::CreateDir(m_outputDir+QDir::separator()+m_imageDirectory);
    Util::CreateDir(m_outputDir+QDir::separator()+m_plotsDirectory);
    Util::CreateDir(m_outputDir+QDir::separator()+m_scriptDirectory);
*/


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



    //    if (m_dataType == QUINT)
    setupLabelFiles(data);



    m_files = data->Get("files").trimmed().simplified().split(",");
    m_coordinates_single_point = data->Get("coordinate_single_point").toLower()=="yes"?1:0;
    m_pixelCutoff = data->Get("object_min_size").toFloat();
    //    m_pixelCutoffMax = data->Get("object_max_size").toFloat();
    m_pixelCutoffMax = 100000; // NOT USED!
    m_areaScale = data->Get("global_pixel_scale").toFloat();
    m_areaSplitting = data->Get("object_splitting").toLower()=="yes"?1:0;

    m_outputRegionNumbers = data->Get("output_region_id").toLower()=="no"?false:true;


    Data::data.m_hasAreaSplitting = m_areaSplitting;
    if (m_dataType==QUINT)
        m_anchorFile = data->Get("xml_anchor_file");
  /*  if (data->m_items.contains("nifti_size"))
        m_niftiSize = data->GetInt("nifti_size");//m_sheet->readNum(12,1);
    else m_niftiSize = 0;*/
    m_xyzScale = data->GetInt("pixel_density");
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

//    nifti.Create(QVector3D(m_niftiSize,m_niftiSize,m_niftiSize),Nifti::DataType::DT_RGB, 24);
 //   nifti.rawData.fill(0);
   // qDebug() << nifti.rawData.count() << m_niftiSize;


    if (m_dataType==NONE) {
        reports.m_reports.push_back(Report("Report", QStringList() << "1", m_background));
        for (Report& r: reports.m_reports)
            r.m_unit = m_units;


    }


}






