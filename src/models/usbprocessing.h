#pragma once
#include <future>

#include <QtCore/QObject>
#include <QtCore/QString>
#include "utils/optional.h"


enum class UsbFormatFS {
	 FAT
	,FAT32
	,ExFAT
	,NTFS
};
Q_ENUMS(UsbFormatFS);

struct UsbProcessTarget {
	Optional<UsbFormatFS> formatFs;
	Optional<QString>     label;
	Optional<QString>     templateFolder;
};

struct UsbDriveInfo {
	QString letter;
	QString label;
};

enum class UsbProcessState {
	 Error = -1
	,Pending
	,Formatting
	,Labeling
	,CopyingTemplate
	,Finished
};
Q_ENUMS(UsbProcessState);


class UsbProcessing : public QObject {
	using State = UsbProcessState;

	class Worker;
	friend class Worker;

	UsbDriveInfo	 m_drive;
	State            m_state;
	int				 m_progress;
	QString          m_info;

	UsbProcessTarget m_target;

	Q_PROPERTY(QString letter   WRITE setLetter READ letter   NOTIFY sgnLetterChanged)
	Q_PROPERTY(QString label    WRITE setLabel  READ label    NOTIFY sgnLabelChanged)
	Q_PROPERTY(State   state                    READ state    NOTIFY sgnStateChanged)
	Q_PROPERTY(int     progress                 READ progress NOTIFY sgnProgress)
	Q_PROPERTY(QString info                     READ info     NOTIFY sgnInfoChanged)
	
public:
	UsbProcessing(UsbDriveInfo info, QObject* parent=Q_NULLPTR);

	std::future<void> process(UsbProcessTarget target);

	//Getters
	QString letter()   const;
	QString label()    const;
	State   state()    const;
	int     progress() const;
	QString info()     const;

public Q_SLOTS:
	//Setters
	void setLetter(QString letter);
	void setLabel(QString label);

Q_SIGNALS:
	//signals
	void sgnLetterChanged(QString newLetter);
	void sgnLabelChanged(QString newLabel);
	void sgnStateChanged(State newState);
	void sgnProgress(int newProgress);
	void sgnInfoChanged(QString newInfo);

};