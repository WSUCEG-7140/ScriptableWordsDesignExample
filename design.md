# Design

This design documents how the ScriptableWords project implements the following @ref Requirements.

@section Project Project Overview

Software Engineering is the application of engineering processes to create software specifications, designs, implementations, tests, and sustainment. This project shows one concrete application of a process to document the design of software. The goal is to produce a useful maintainable software design document with a minimum of extra effort beyond the effort that would be expended on designing and implementing software. In other words, the goal is to minimize any extra effort needed *document* the design that happens whether it is documented or not.

The basic approach is to use the free open-source cross-platform multi-language [Doxygen](https://www.doxygen.nl/index.html) program to extract formatted comments from software.

One of the key features of a design is traceability to requirements (or User Stories or Issues). How do you know when you are done designing? You are done when the design describes HOW (in a general sense) each of the requirements will be met by software. The actual implementation of software ultimately describes HOW requirements are met in the most specific way possible, and implementations need to trace back to design and requirements too, but little or no implementation is needed during design. To trace design to requirements, Doxygen @anchore and custom Doxygen @req tags are used in formatted comments. Together, the tags provide traceability from design to requirements and from requirements to design. Traceability from design to Requirements can succinctly answer the question, "Why does this deigned element exist?" It exists to fully or partially meet referenced requirements. Doxygen makes convenient hyperlinks so clicking on a requirement referenced in a design takes the reader directly to the text of the referenced requirement.

 One advantage of creating design documentation directly in source code is to mitigate the problem that code changes but the corresponding documentation does not. By co-locating the code and the documentation, there is a better chance that a change to one will be reflected in the other. It is also convenient to have the design right before you eyes when implementing the design in code. The programmer does not need to look far.

 Another advantage is that printing design documentation may almost always be avoided by using the generated electronic documentation instead. If somebody needs the most up to date design information, generate the document directly from the source code on demand. It only takes seconds. Documentation generation may even be added to automated software build systems.

@section ModelViewPresenter Model View Presenter

This overarching design applies the @designpattern [Model View Presenter](https://en.wikipedia.org/wiki/Model–view–presenter) @designpattern [Software Design Pattern](https://en.wikipedia.org/wiki/Software_design_pattern) that is a derivation of the venerable [Model View Controller](https://en.wikipedia.org/wiki/Model–view–controller) Design Pattern. 

## Model

@ref WSU::Model

## View

## Presenter

@ref WSU::Controller

