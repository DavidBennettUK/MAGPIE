#-------------------------------------------------
#
# Project created by QtCreator 2012-10-18T17:39:45
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = MAGPIE
TEMPLATE = app

DEPENDPATH += . \
    src \
INCLUDEPATH += . \
    src

SOURCES += src/main.cpp \
    src/widgets/LawnViewWidget.cpp \
    src/gp/Individual.cpp \
    src/gp/Node.cpp \
    src/scenarios/common/nodes/Prog2Node.cpp \
    src/scenarios/lawnmower/nodes/LeftNode.cpp \
    src/scenarios/lawnmower/Environment.cpp \
    src/gp/Scenario.cpp \
    src/gp/Generation.cpp \
    src/windows/PlayerWindow.cpp \
    src/scenarios/lawnmower/nodes/MowNode.cpp \
    src/widgets/TreeViewWidget.cpp \
    src/windows/TreeWindow.cpp \
    src/windows/GenerationWindow.cpp \
    src/windows/WorkspaceWindow.cpp \
    src/DrawTreeBuilder.cpp \
    src/DrawNode.cpp \
    src/gp/Crossover.cpp \
    src/windows/TournamentWindow.cpp \
    src/gp/TournamentSelection.cpp \
    src/gp/RouletteSelection.cpp \
    src/widgets/RouletteWidget.cpp \
    src/windows/RouletteWindow.cpp \
    src/gp/Mutation.cpp \
    src/widgets/CrossoverWidget.cpp \
    src/windows/CrossoverWindow.cpp \
    src/windows/LessonWindow.cpp \
    src/lessons/IntroductionLesson.cpp \
    src/lessons/Lesson.cpp \
    src/windows/StepWindow.cpp \
    src/lessons/LessonStep.cpp \
    src/lessons/SelectionLesson.cpp \
    src/lessons/TreeLesson.cpp \
    src/lessons/OperatorsLesson.cpp \
    src/scenarios/lawnmower/LawnmowerScenario.cpp \
    src/scenarios/lawnmower/Lawnmower.cpp \
    src/scenarios/lawnmower/LawnmowerFitness.cpp \
    src/gp/TreeFactory.cpp \
    src/windows/MutationWindow.cpp \
    src/widgets/MutationWidget.cpp \
    src/lessons/GPRunLesson.cpp \
    src/windows/GPRunWindow.cpp \
    src/lessons/ExperimentLesson.cpp \
    src/lib/qcustomplot.cpp \
    src/windows/GraphWindow.cpp \
    src/widgets/GraphWidget.cpp \
    src/scenarios/lawnmowerMulti/LawnmowerMultiScenario.cpp \
    src/scenarios/lawnmowerMulti/nodes/IfObstacleAheadNode.cpp \
    src/scenarios/lawnmowerMulti/EnvironmentMulti.cpp \
    src/scenarios/lawnmowerMulti/LawnmowerMulti.cpp \
    src/lessons/MultiObjectiveLesson.cpp \
    src/widgets/LawnViewMultiWidget.cpp \
    src/scenarios/lawnmowerMulti/LawnmowerMultiFitness.cpp \
    src/scenarios/lawnmowerMulti/nodes/MowMultiNode.cpp \
    src/scenarios/ant/AntScenario.cpp \
    src/scenarios/ant/nodes/IfFoodAheadNode.cpp \
    src/scenarios/ant/AntFitness.cpp \
    src/scenarios/ant/Ant.cpp \
    src/scenarios/ant/nodes/AntLeftNode.cpp \
    src/scenarios/ant/nodes/ForwardNode.cpp \
    src/widgets/AntViewWidget.cpp \
    src/lessons/AntLesson.cpp \
    src/scenarios/common/nodes/Prog3Node.cpp \
    src/scenarios/ant/nodes/AntRightNode.cpp

HEADERS  += \
    src/widgets/LawnViewWidget.h \
    src/gp/Individual.h \
    src/common.h \
    src/gp/Node.h \
    src/scenarios/common/nodes/Prog2Node.h \
    src/scenarios/lawnmower/nodes/LeftNode.h \
    src/scenarios/lawnmower/Environment.h \
    src/gp/Scenario.h \
    src/gp/Generation.h \
    src/windows/PlayerWindow.h \
    src/scenarios/lawnmower/nodes/MowNode.h \
    src/gp/Fitness.h \
    src/widgets/TreeViewWidget.h \
    src/windows/TreeWindow.h \
    src/windows/GenerationWindow.h \
    src/windows/WorkspaceWindow.h \
    src/DrawTreeBuilder.h \
    src/DrawNode.h \
    src/gp/Selection.h \
    src/gp/Crossover.h \
    src/windows/TournamentWindow.h \
    src/gp/TournamentSelection.h \
    src/gp/RouletteSelection.h \
    src/widgets/RouletteWidget.h \
    src/windows/RouletteWindow.h \
    src/glUtil.h \
    src/gp/Mutation.h \
    src/widgets/CrossoverWidget.h \
    src/windows/CrossoverWindow.h \
    src/windows/LessonWindow.h \
    src/lessons/IntroductionLesson.h \
    src/lessons/Lesson.h \
    src/windows/StepWindow.h \
    src/lessons/LessonStep.h \
    src/lessons/SelectionLesson.h \
    src/lessons/TreeLesson.h \
    src/lessons/OperatorsLesson.h \
    src/scenarios/lawnmower/LawnmowerScenario.h \
    src/scenarios/lawnmower/Lawnmower.h \
    src/scenarios/lawnmower/LawnmowerFitness.h \
    src/gp/TreeFactory.h \
    src/windows/MutationWindow.h \
    src/widgets/MutationWidget.h \
    src/lessons/GPRunLesson.h \
    src/windows/GPRunWindow.h \
    src/lessons/ExperimentLesson.h \
    src/lib/qcustomplot.h \
    src/windows/GraphWindow.h \
    src/widgets/GraphWidget.h \
    src/gp/Parameter.h \
    src/gp/IntValue.h \
    src/widgets/PlayerWidget.h \
    src/scenarios/lawnmowerMulti/LawnmowerMultiScenario.h \
    src/scenarios/lawnmowerMulti/EnvironmentMulti.h \
    src/scenarios/lawnmowerMulti/LawnmowerMulti.h \
    src/scenarios/lawnmowerMulti/nodes/IfObstacleAheadNode.h \
    src/lessons/MultiObjectiveLesson.h \
    src/widgets/LawnViewMultiWidget.h \
    src/scenarios/lawnmowerMulti/LawnmowerMultiFitness.h \
    src/scenarios/lawnmowerMulti/nodes/MowMultiNode.h \
    src/scenarios/ant/AntScenario.h \
    src/scenarios/ant/nodes/IfFoodAheadNode.h \
    src/scenarios/ant/AntFitness.h \
    src/scenarios/ant/Ant.h \
    src/scenarios/ant/nodes/AntLeftNode.h \
    src/scenarios/ant/nodes/ForwardNode.h \
    src/widgets/AntViewWidget.h \
    src/lessons/AntLesson.h \
    src/scenarios/common/nodes/Prog3Node.h \
    src/scenarios/ant/nodes/AntRightNode.h

FORMS    +=

RESOURCES += \
    resources/ImagesResource.qrc
    
RC_FILE = resources/MAGPIE.rc

ICON = resources/icon.icns
